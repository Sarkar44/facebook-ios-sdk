/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "FBSDKAppEventsConfigurationManager.h"

#import <FBSDKCoreKit_Basics/FBSDKCoreKit_Basics.h>

#import "FBSDKDataPersisting.h"
#import "FBSDKGraphRequestConnecting.h"
#import "FBSDKGraphRequestConnectionFactory.h"
#import "FBSDKGraphRequestFactoryProtocol.h"
#import "FBSDKSettingsProtocol.h"

static NSString *const FBSDKAppEventsConfigurationKey = @"com.facebook.sdk:FBSDKAppEventsConfiguration";
static NSString *const FBSDKAppEventsConfigurationTimestampKey = @"com.facebook.sdk:FBSDKAppEventsConfigurationTimestamp";
static const NSTimeInterval kTimeout = 4.0;

@interface FBSDKAppEventsConfigurationManager ()

@property (nullable, nonatomic) id<FBSDKDataPersisting> store;
@property (nullable, nonatomic) id<FBSDKSettings> settings;
@property (nullable, nonatomic) id<FBSDKGraphRequestFactory> graphRequestFactory;
@property (nullable, nonatomic) id<FBSDKGraphRequestConnectionFactory> graphRequestConnectionFactory;
@property (nonnull, nonatomic) FBSDKAppEventsConfiguration *configuration;
@property (nonatomic) BOOL isLoadingConfiguration;
@property (nonatomic) BOOL hasRequeryFinishedForAppStart;
@property (nullable, nonatomic) NSDate *timestamp;
@property (nullable, nonatomic) NSMutableArray *completionBlocks;

@end

@implementation FBSDKAppEventsConfigurationManager

static dispatch_once_t sharedConfigurationManagerNonce;

// Transitional singleton introduced as a way to change the usage semantics
// from a type-based interface to an instance-based interface.
// The goal of the refactor is to move callsites from:
// ClassWithoutUnderlyingInstance -> ClassRelyingOnUnderlyingInstance -> Instance
+ (FBSDKAppEventsConfigurationManager *)shared
{
  static id instance;
  dispatch_once(&sharedConfigurationManagerNonce, ^{
    instance = [self new];
  });
  return instance;
}

+ (void)     configureWithStore:(id<FBSDKDataPersisting>)store
                       settings:(id<FBSDKSettings>)settings
            graphRequestFactory:(id<FBSDKGraphRequestFactory>)graphRequestFactory
  graphRequestConnectionFactory:(id<FBSDKGraphRequestConnectionFactory>)graphRequestConnectionFactory
{
  [self.shared configureWithStore:store
                         settings:settings
              graphRequestFactory:graphRequestFactory
    graphRequestConnectionFactory:graphRequestConnectionFactory];
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
- (void)     configureWithStore:(id<FBSDKDataPersisting>)store
                       settings:(id<FBSDKSettings>)settings
            graphRequestFactory:(id<FBSDKGraphRequestFactory>)graphRequestFactory
  graphRequestConnectionFactory:(id<FBSDKGraphRequestConnectionFactory>)graphRequestConnectionFactory
{
  self.store = store;
  self.settings = settings;
  self.graphRequestFactory = graphRequestFactory;
  self.graphRequestConnectionFactory = graphRequestConnectionFactory;
  id data = [self.store objectForKey:FBSDKAppEventsConfigurationKey];
  if ([data isKindOfClass:NSData.class]) {
    if (@available(iOS 11.0, tvOS 11.0, *)) {
      self.configuration = [NSKeyedUnarchiver unarchivedObjectOfClass:FBSDKAppEventsConfiguration.class fromData:data error:nil];
    } else {
      self.configuration = [NSKeyedUnarchiver unarchiveObjectWithData:data];
    }
  }
  if (!self.configuration) {
    self.configuration = [FBSDKAppEventsConfiguration defaultConfiguration];
  }
  self.completionBlocks = [NSMutableArray new];
  self.timestamp = [self.store objectForKey:FBSDKAppEventsConfigurationTimestampKey];
}

#pragma clang diagnostic pop

+ (FBSDKAppEventsConfiguration *)cachedAppEventsConfiguration
{
  return self.shared.cachedAppEventsConfiguration;
}

- (FBSDKAppEventsConfiguration *)cachedAppEventsConfiguration
{
  return self.configuration;
}

+ (void)loadAppEventsConfigurationWithBlock:(FBSDKAppEventsConfigurationManagerBlock)block
{
  [self.shared loadAppEventsConfigurationWithBlock:block];
}

- (void)loadAppEventsConfigurationWithBlock:(FBSDKAppEventsConfigurationManagerBlock)block
{
  NSString *appID = self.settings.appID;
  @synchronized(self) {
    [FBSDKTypeUtility array:self.completionBlocks addObject:block];
    if (!appID || (self.hasRequeryFinishedForAppStart && [self _isTimestampValid])) {
      for (FBSDKAppEventsConfigurationManagerBlock completionBlock in self.completionBlocks) {
        completionBlock();
      }
      [self.completionBlocks removeAllObjects];
      return;
    }
    if (self.isLoadingConfiguration) {
      return;
    }
    self.isLoadingConfiguration = true;
    id<FBSDKGraphRequest> request = [self.graphRequestFactory createGraphRequestWithGraphPath:appID
                                                                                   parameters:@{
                                       @"fields" : [NSString stringWithFormat:@"app_events_config.os_version(%@)", [UIDevice currentDevice].systemVersion]
                                     }];
    id<FBSDKGraphRequestConnecting> requestConnection = [self.graphRequestConnectionFactory createGraphRequestConnection];
    requestConnection.timeout = kTimeout;
    [requestConnection addRequest:request completion:^(id<FBSDKGraphRequestConnecting> connection, id result, NSError *error) {
      [self _processResponse:result error:error];
    }];
    [requestConnection start];
  }
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
+ (void)_processResponse:(id)response
                   error:(NSError *)error
{
  [self.shared _processResponse:response error:error];
}

- (void)_processResponse:(id)response
                   error:(NSError *)error
{
  NSDate *date = [NSDate date];
  @synchronized(self) {
    self.isLoadingConfiguration = NO;
    self.hasRequeryFinishedForAppStart = YES;
    if (error) {
      return;
    }
    self.configuration = [[FBSDKAppEventsConfiguration alloc] initWithJSON:response];
    self.timestamp = date;
    for (FBSDKAppEventsConfigurationManagerBlock completionBlock in self.completionBlocks) {
      completionBlock();
    }
    [self.completionBlocks removeAllObjects];
  }
  NSData *data = [NSKeyedArchiver archivedDataWithRootObject:self.configuration];
  [self.store setObject:data forKey:FBSDKAppEventsConfigurationKey];
  [self.store setObject:date forKey:FBSDKAppEventsConfigurationTimestampKey];
}

#pragma clang diagnostic pop

- (BOOL)_isTimestampValid
{
  return self.timestamp && [[NSDate date] timeIntervalSinceDate:self.timestamp] < 3600;
}

#if DEBUG && FBTEST

+ (void)reset
{
  [self.shared reset];
}

- (void)reset
{
  // Reset the nonce so that a new instance will be created.
  if (sharedConfigurationManagerNonce) {
    sharedConfigurationManagerNonce = 0;
  }
}

#endif

@end
