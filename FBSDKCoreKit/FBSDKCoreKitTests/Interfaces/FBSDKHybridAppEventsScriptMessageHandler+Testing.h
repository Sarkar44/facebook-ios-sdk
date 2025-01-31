/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "FBSDKHybridAppEventsScriptMessageHandler.h"

@protocol FBSDKEventLogging;

NS_ASSUME_NONNULL_BEGIN

@interface FBSDKHybridAppEventsScriptMessageHandler (Testing)

@property (nonatomic) id<FBSDKEventLogging> eventLogger;

- (instancetype)initWithEventLogger:(id<FBSDKEventLogging>)eventLogger
NS_SWIFT_NAME(init(eventLogger:));

@end

NS_ASSUME_NONNULL_END
