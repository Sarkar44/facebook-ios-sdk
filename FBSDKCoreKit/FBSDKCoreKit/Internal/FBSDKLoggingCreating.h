/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>

#import "FBSDKLoggingBehavior.h"
#import "FBSDKLogging.h"

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(LoggingCreating)
@protocol FBSDKLoggingCreating

- (id<FBSDKLogging>)createLoggerWithLoggingBehavior:(FBSDKLoggingBehavior)loggingBehavior;

@end

NS_ASSUME_NONNULL_END
