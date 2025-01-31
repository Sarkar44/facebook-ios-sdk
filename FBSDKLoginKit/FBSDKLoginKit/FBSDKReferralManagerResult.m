/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#if !TARGET_OS_TV

#import "FBSDKReferralManagerResult.h"

@implementation FBSDKReferralManagerResult

- (instancetype)initWithReferralCodes:(nullable NSArray<FBSDKReferralCode *> *)referralCodes
                          isCancelled:(BOOL)isCancelled
{
  if ((self = [super init])) {
    _referralCodes = referralCodes;
    _isCancelled = isCancelled;
  }
  ;
  return self;
}

@end

#endif
