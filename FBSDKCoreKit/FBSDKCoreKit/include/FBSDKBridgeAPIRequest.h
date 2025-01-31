/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#if !TARGET_OS_TV

#import <Foundation/Foundation.h>

#import <FBSDKCoreKit/FBSDKBridgeAPIProtocolType.h>
#import <FBSDKCoreKit/FBSDKBridgeAPIRequest.h>
#import <FBSDKCoreKit/FBSDKBridgeAPIRequestProtocol.h>
#import <FBSDKCoreKit/FBSDKURLScheme.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Internal Type exposed to facilitate transition to Swift.
 API Subject to change or removal without warning. Do not use.

 @warning UNSAFE - DO NOT USE
 */
NS_SWIFT_NAME(BridgeAPIRequest)
@interface FBSDKBridgeAPIRequest : NSObject <NSCopying, FBSDKBridgeAPIRequest>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
+ (nullable instancetype)bridgeAPIRequestWithProtocolType:(FBSDKBridgeAPIProtocolType)protocolType
                                                   scheme:(FBSDKURLScheme)scheme
                                               methodName:(nullable NSString *)methodName
                                            methodVersion:(nullable NSString *)methodVersion
                                               parameters:(nullable NSDictionary<NSString *, id> *)parameters
                                                 userInfo:(nullable NSDictionary<NSString *, id> *)userInfo;

@property (nonatomic, copy, readonly) NSString *actionID;
@property (nonatomic, nullable, copy, readonly) NSString *methodName;
@property (nonatomic, nullable, copy, readonly) NSString *methodVersion;
@property (nonatomic, nullable, copy, readonly) NSDictionary<NSString *, id> *parameters;
@property (nonatomic, assign, readonly) FBSDKBridgeAPIProtocolType protocolType;
@property (nonatomic, copy, readonly) FBSDKURLScheme scheme;
@property (nonatomic, nullable, copy, readonly) NSDictionary<NSString *, id> *userInfo;

- (nullable NSURL *)requestURL:(NSError *_Nullable *)errorRef;

@end

NS_ASSUME_NONNULL_END

#endif
