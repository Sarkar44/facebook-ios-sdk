/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "FBSDKPaymentObserver.h"
#import "FBSDKPaymentProductRequestorCreating.h"

@class SKPaymentQueue;

NS_ASSUME_NONNULL_BEGIN

@interface FBSDKPaymentObserver (Testing)

@property (nonatomic, readonly) SKPaymentQueue *paymentQueue;
@property (nonatomic, readonly) id<FBSDKPaymentProductRequestorCreating> requestorFactory;

- (instancetype)initWithPaymentQueue:(SKPaymentQueue *)paymentQueue
      paymentProductRequestorFactory:(id<FBSDKPaymentProductRequestorCreating>)paymentProductRequestorFactory
NS_SWIFT_NAME(init(paymentQueue:paymentProductRequestorFactory:));

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;

@end

NS_ASSUME_NONNULL_END
