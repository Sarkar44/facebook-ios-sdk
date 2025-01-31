/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(TokenStringProviding)
@protocol FBSDKTokenStringProviding

/**
  Return the token string of the current access token.

  Internal Type exposed to facilitate transition to Swift.
  API Subject to change or removal without warning. Do not use.

  @warning UNSAFE - DO NOT USE
*/

@property (class, nonatomic, copy, nullable, readonly) NSString * tokenString;

@end

NS_ASSUME_NONNULL_END
