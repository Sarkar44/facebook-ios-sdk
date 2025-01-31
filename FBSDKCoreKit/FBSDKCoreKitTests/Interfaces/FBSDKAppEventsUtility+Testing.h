/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "FBSDKAppEventsUtility.h"

NS_ASSUME_NONNULL_BEGIN

@interface FBSDKAppEventsUtility (Testing)

@property (nullable, class, nonatomic) ASIdentifierManager *cachedAdvertiserIdentifierManager;

- (ASIdentifierManager *)_asIdentifierManagerWithShouldUseCachedManager:(BOOL)useCachedManagerIfAvailable
                                               dynamicFrameworkResolver:(id<FBSDKDynamicFrameworkResolving>)dynamicFrameworkResolver
NS_SWIFT_NAME(asIdentifierManager(shouldUseCachedManager:dynamicFrameworkResolver:));

@end

NS_ASSUME_NONNULL_END
