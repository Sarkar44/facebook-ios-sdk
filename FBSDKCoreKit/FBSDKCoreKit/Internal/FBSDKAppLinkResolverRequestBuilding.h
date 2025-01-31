/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>

@protocol FBSDKGraphRequest;

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(AppLinkResolverRequestBuilding)
@protocol FBSDKAppLinkResolverRequestBuilding

- (id<FBSDKGraphRequest> _Nonnull)requestForURLs:(NSArray<NSURL *> * _Nonnull)urls;
- (NSString* _Nullable)getIdiomSpecificField;

@end

NS_ASSUME_NONNULL_END
