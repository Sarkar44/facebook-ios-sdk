/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>
#import <FBSDKCoreKit/FBSDKKeychainStoreProtocol.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(KeychainStoreProviding)
@protocol FBSDKKeychainStoreProviding

- (nonnull id<FBSDKKeychainStore>)createKeychainStoreWithService:(NSString *)service
                                                     accessGroup:(nullable NSString *)accessGroup;
@end

NS_ASSUME_NONNULL_END
