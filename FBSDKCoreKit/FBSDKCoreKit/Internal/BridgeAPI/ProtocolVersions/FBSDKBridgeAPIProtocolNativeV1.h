/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#if !TARGET_OS_TV

#import <UIKit/UIKit.h>

#import "FBSDKBridgeAPIProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@protocol FBSDKPasteboard;

typedef struct
{
  __unsafe_unretained NSString *bridgeArgs;
  __unsafe_unretained NSString *methodArgs;
  __unsafe_unretained NSString *methodVersion;
} FBSDKBridgeAPIProtocolNativeV1OutputKeysStruct;
FOUNDATION_EXPORT const FBSDKBridgeAPIProtocolNativeV1OutputKeysStruct FBSDKBridgeAPIProtocolNativeV1OutputKeys;

typedef struct
{
  __unsafe_unretained NSString *actionID;
  __unsafe_unretained NSString *appIcon;
  __unsafe_unretained NSString *appName;
  __unsafe_unretained NSString *sdkVersion;
} FBSDKBridgeAPIProtocolNativeV1BridgeParameterOutputKeysStruct;
FOUNDATION_EXPORT const FBSDKBridgeAPIProtocolNativeV1BridgeParameterOutputKeysStruct FBSDKBridgeAPIProtocolNativeV1BridgeParameterOutputKeys;

typedef struct
{
  __unsafe_unretained NSString *bridgeArgs;
  __unsafe_unretained NSString *methodResults;
} FBSDKBridgeAPIProtocolNativeV1InputKeysStruct;
FOUNDATION_EXPORT const FBSDKBridgeAPIProtocolNativeV1InputKeysStruct FBSDKBridgeAPIProtocolNativeV1InputKeys;

typedef struct
{
  __unsafe_unretained NSString *actionID;
  __unsafe_unretained NSString *error;
} FBSDKBridgeAPIProtocolNativeV1BridgeParameterInputKeysStruct;
FOUNDATION_EXPORT const FBSDKBridgeAPIProtocolNativeV1BridgeParameterInputKeysStruct FBSDKBridgeAPIProtocolNativeV1BridgeParameterInputKeys;

NS_SWIFT_NAME(BridgeAPIProtocolNativeV1)
@interface FBSDKBridgeAPIProtocolNativeV1 : NSObject <FBSDKBridgeAPIProtocol>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithAppScheme:(nullable NSString *)appScheme;
- (instancetype)initWithAppScheme:(nullable NSString *)appScheme
                       pasteboard:(nullable id<FBSDKPasteboard>)pasteboard
              dataLengthThreshold:(NSUInteger)dataLengthThreshold
                   includeAppIcon:(BOOL)includeAppIcon
NS_DESIGNATED_INITIALIZER;

@property (nullable, nonatomic, copy, readonly) NSString *appScheme;
@property (nonatomic, assign, readonly) NSUInteger dataLengthThreshold;
@property (nonatomic, assign, readonly, getter=shouldIncludeAppIcon) BOOL includeAppIcon;
@property (nullable, nonatomic, strong, readonly) id<FBSDKPasteboard> pasteboard;

@end

#endif

NS_ASSUME_NONNULL_END
