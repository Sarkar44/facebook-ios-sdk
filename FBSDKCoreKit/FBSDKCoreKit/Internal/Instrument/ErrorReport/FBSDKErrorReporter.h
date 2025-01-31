/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>

#import "FBSDKError+Internal.h"
#import "FBSDKErrorReporting.h"

@protocol FBSDKGraphRequestFactory;
@protocol FBSDKFileManaging;
@protocol FBSDKSettings;
@protocol FBSDKFileDataExtracting;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(ErrorReporter)
@interface FBSDKErrorReporter : NSObject <FBSDKErrorReporting>

@property (class, nonatomic, readonly) FBSDKErrorReporter *shared;

@property (nonatomic, strong) id<FBSDKGraphRequestFactory> graphRequestFactory;
@property (nonatomic, strong) id<FBSDKFileManaging> fileManager;
@property (nonatomic, strong) id<FBSDKSettings> settings;
@property (nonatomic, strong) Class<FBSDKFileDataExtracting> dataExtractor;
@property (nonatomic, readonly, strong) NSString *directoryPath;
@property (nonatomic) BOOL isEnabled;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (void)saveError:(NSInteger)errorCode
      errorDomain:(NSErrorDomain)errorDomain
          message:(nullable NSString *)message;

- (instancetype)initWithGraphRequestFactory:(id<FBSDKGraphRequestFactory>)graphRequestFactory
                                 fileManager:(id<FBSDKFileManaging>)fileManager
                                    settings:(id<FBSDKSettings>)settings
                           fileDataExtractor:(Class<FBSDKFileDataExtracting>)dataExtractor;
- (void)enable;

@end

NS_ASSUME_NONNULL_END
