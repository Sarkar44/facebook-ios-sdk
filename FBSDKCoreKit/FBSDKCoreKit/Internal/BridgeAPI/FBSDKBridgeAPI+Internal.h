/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "FBSDKBridgeAPI.h"

NS_ASSUME_NONNULL_BEGIN

@interface FBSDKBridgeAPI (Internal)

- (void)openURLWithAuthenticationSession:(NSURL *)url;
- (void)setSessionCompletionHandlerFromHandler:(void (^)(BOOL, NSError *))handler;

@end

NS_ASSUME_NONNULL_END
