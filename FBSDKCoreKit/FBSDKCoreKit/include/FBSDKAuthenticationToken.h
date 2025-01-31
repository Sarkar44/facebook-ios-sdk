/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>


@class FBSDKAuthenticationTokenClaims;
@protocol FBSDKTokenCaching;

NS_ASSUME_NONNULL_BEGIN

/**
 Represent an AuthenticationToken used for a login attempt
*/
NS_SWIFT_NAME(AuthenticationToken)
@interface FBSDKAuthenticationToken : NSObject<NSCopying, NSObject, NSSecureCoding>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
  The "global" authentication token that represents the currently logged in user.

 The `currentAuthenticationToken` represents the authentication token of the
 current user and can be used by a client to verify an authentication attempt.
 */
@property (class, nonatomic, copy, nullable) FBSDKAuthenticationToken *currentAuthenticationToken;

/**
 The raw token string from the authentication response
 */
@property (nonatomic, copy, readonly) NSString *tokenString;

/**
 The nonce from the decoded authentication response
 */
@property (nonatomic, copy, readonly) NSString *nonce;

/**
  The graph domain where the user is authenticated.
 */
@property (nonatomic, copy, readonly) NSString *graphDomain;

/**
  Returns the claims encoded in the AuthenticationToken
 */
- (nullable FBSDKAuthenticationTokenClaims *)claims;

/**
 Internal Type exposed to facilitate transition to Swift.
 API Subject to change or removal without warning. Do not use.

 @warning UNSAFE - DO NOT USE
 */
@property (nullable, class, nonatomic, copy) id<FBSDKTokenCaching> tokenCache;

@end

NS_ASSUME_NONNULL_END
