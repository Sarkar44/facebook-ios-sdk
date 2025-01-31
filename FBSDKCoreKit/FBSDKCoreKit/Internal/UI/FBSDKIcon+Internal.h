/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <FBSDKCoreKit/FBSDKIcon.h>

NS_ASSUME_NONNULL_BEGIN

@interface FBSDKIcon (Internal)

- (nullable UIImage *)imageWithSize:(CGSize)size
NS_SWIFT_NAME(image(size:));

- (nullable UIImage *)imageWithSize:(CGSize)size scale:(CGFloat)scale
NS_SWIFT_NAME(image(size:scale:));

- (nullable UIImage *)imageWithSize:(CGSize)size color:(UIColor *)color
NS_SWIFT_NAME(image(size:color:));

- (nullable UIImage *)imageWithSize:(CGSize)size scale:(CGFloat)scale color:(UIColor *)color
NS_SWIFT_NAME(image(size:scale:color:));

@end

NS_ASSUME_NONNULL_END
