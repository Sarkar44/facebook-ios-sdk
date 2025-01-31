/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>
#import <XCTest/XCTest.h>

NS_ASSUME_NONNULL_BEGIN

// Hack to be able to test from Swift code that NSExceptions were raised.
@interface XCTestCase (Testing)

- (void)assertRaisesExceptionWithMessage:(NSString *)message block:(void (^)(void))block
NS_SWIFT_NAME(assertRaisesException(message:block:));

@end

NS_ASSUME_NONNULL_END
