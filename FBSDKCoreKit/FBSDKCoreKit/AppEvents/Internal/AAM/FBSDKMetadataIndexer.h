/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#if !TARGET_OS_TV

 #import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(MetadataIndexer)
@interface FBSDKMetadataIndexer : NSObject

@property (class, nonatomic, readonly) FBSDKMetadataIndexer *shared;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (void)enable;

@end

NS_ASSUME_NONNULL_END

#endif
