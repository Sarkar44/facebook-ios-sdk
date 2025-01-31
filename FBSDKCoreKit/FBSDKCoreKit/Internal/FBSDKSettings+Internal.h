/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <FBSDKCoreKit/FBSDKAdvertisingTrackingStatus.h>
#import <FBSDKCoreKit/FBSDKSettings.h>

#define DATA_PROCESSING_OPTIONS         @"data_processing_options"
#define DATA_PROCESSING_OPTIONS_COUNTRY @"data_processing_options_country"
#define DATA_PROCESSING_OPTIONS_STATE   @"data_processing_options_state"

NS_ASSUME_NONNULL_BEGIN

@protocol FBSDKTokenCaching;
@protocol FBSDKDataPersisting;
@protocol FBSDKAppEventsConfigurationProviding;
@protocol FBSDKInfoDictionaryProviding;
@protocol FBSDKEventLogging;

@interface FBSDKSettings (Internal)

@property (class, nullable, nonatomic, readonly, copy) NSString *graphAPIDebugParamValue;
@property (nonatomic) BOOL shouldUseTokenOptimizations;
@property (nonatomic, nullable) NSDictionary<NSString *, id> *persistableDataProcessingOptions;

+ (void)      configureWithStore:(nonnull id<FBSDKDataPersisting>)store
  appEventsConfigurationProvider:(nonnull Class<FBSDKAppEventsConfigurationProviding>)provider
          infoDictionaryProvider:(nonnull id<FBSDKInfoDictionaryProviding>)infoDictionaryProvider
                     eventLogger:(nonnull id<FBSDKEventLogging>)eventLogger
  NS_SWIFT_NAME(configure(store:appEventsConfigurationProvider:infoDictionaryProvider:eventLogger:));

+ (nullable NSObject<FBSDKTokenCaching> *)tokenCache;

+ (void)setTokenCache:(nullable NSObject<FBSDKTokenCaching> *)tokenCache;

+ (FBSDKAdvertisingTrackingStatus)advertisingTrackingStatus;

+ (void)setAdvertiserTrackingStatus:(FBSDKAdvertisingTrackingStatus)status;

+ (BOOL)isDataProcessingRestricted;

+ (void)recordSetAdvertiserTrackingEnabled;

+ (BOOL)isEventDelayTimerExpired;

+ (BOOL)isSetATETimeExceedsInstallTime;

+ (NSDate *_Nullable)getInstallTimestamp;

+ (NSDate *_Nullable)getSetAdvertiserTrackingEnabledTimestamp;

- (void)recordInstall;

- (void)logWarnings;

- (void)logIfSDKSettingsChanged;

@end

NS_ASSUME_NONNULL_END
