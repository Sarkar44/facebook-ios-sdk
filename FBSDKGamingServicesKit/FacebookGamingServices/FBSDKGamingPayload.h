/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>

@class FBSDKURL;

NS_ASSUME_NONNULL_BEGIN

extern NSString *const kGamingPayload;
extern NSString *const kGamingPayloadGameRequestID;
extern NSString *const kGamingPayloadContextTokenID;

NS_SWIFT_NAME(GamingPayload)
@interface FBSDKGamingPayload : NSObject

@property (nonatomic, strong, nonnull) FBSDKURL *URL;
@property (nonatomic, strong, readonly) NSString *payload;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithURL:(FBSDKURL * _Nonnull)url
NS_SWIFT_NAME(initWith(URL:));

@end

NS_ASSUME_NONNULL_END
