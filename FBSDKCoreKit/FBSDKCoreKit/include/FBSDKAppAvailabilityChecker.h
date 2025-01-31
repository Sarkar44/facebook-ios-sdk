/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <FBSDKCoreKit/FBSDKInternalUtility.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(AppAvailabilityChecker)
@protocol FBSDKAppAvailabilityChecker

/**
 Internal Type exposed to facilitate transition to Swift.
 API Subject to change or removal without warning. Do not use.

 @warning UNSAFE - DO NOT USE
 */
@property (nonatomic, assign, readonly) BOOL isMessengerAppInstalled;
/**
 Internal Type exposed to facilitate transition to Swift.
 API Subject to change or removal without warning. Do not use.

 @warning UNSAFE - DO NOT USE
 */
@property (nonatomic, assign, readonly) BOOL isFacebookAppInstalled;

@end

NS_ASSUME_NONNULL_END
