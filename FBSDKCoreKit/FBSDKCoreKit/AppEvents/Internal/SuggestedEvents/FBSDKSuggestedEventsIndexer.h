/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#if !TARGET_OS_TV

 #import <Foundation/Foundation.h>
 #import "FBSDKSuggestedEventsIndexerProtocol.h"


NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(SuggestedEventsIndexer)
@interface FBSDKSuggestedEventsIndexer : NSObject <FBSDKSuggestedEventsIndexer>

@property (class, nonatomic, strong, readonly) FBSDKSuggestedEventsIndexer *shared;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (void)enable;

@end

NS_ASSUME_NONNULL_END

#endif
