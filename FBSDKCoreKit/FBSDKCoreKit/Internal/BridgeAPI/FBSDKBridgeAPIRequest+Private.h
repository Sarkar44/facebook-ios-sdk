/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#if !TARGET_OS_TV

#import "FBSDKBridgeAPIProtocol.h"
#import "FBSDKBridgeAPIRequest.h"
#import "FBSDKInternalURLOpener.h"
#import "FBSDKInternalUtility.h"
#import "FBSDKSettings.h"

NS_ASSUME_NONNULL_BEGIN

@interface FBSDKBridgeAPIRequest ()

@property (class, nullable, nonatomic) id<FBSDKInternalURLOpener> internalURLOpener;
@property (class, nullable, nonatomic) id<FBSDKInternalUtility> internalUtility;
@property (class, nullable, nonatomic) id<FBSDKSettings> settings;

@property (nonatomic, readwrite) id<FBSDKBridgeAPIProtocol> protocol;

+ (void)configureWithInternalURLOpener:(id<FBSDKInternalURLOpener>)internalURLOpener
                       internalUtility:(id<FBSDKInternalUtility>)internalUtility
                              settings:(id<FBSDKSettings>)settings;

- (nullable instancetype)initWithProtocol:(nullable id<FBSDKBridgeAPIProtocol>)protocol
                             protocolType:(FBSDKBridgeAPIProtocolType)protocolType
                                   scheme:(FBSDKURLScheme)scheme
                               methodName:(nullable NSString *)methodName
                            methodVersion:(nullable NSString *)methodVersion
                               parameters:(nullable NSDictionary<NSString *, id> *)parameters
                                 userInfo:(nullable NSDictionary<NSString *, id> *)userInfo
NS_DESIGNATED_INITIALIZER
NS_SWIFT_NAME(init(protocol:protocolType:scheme:methodName:methodVersion:parameters:userInfo:));

@end

NS_ASSUME_NONNULL_END

#endif
