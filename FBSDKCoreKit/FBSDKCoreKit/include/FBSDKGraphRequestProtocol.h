/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>

#import <FBSDKCoreKit/FBSDKGraphRequestHTTPMethod.h>
#import <FBSDKCoreKit/FBSDKGraphRequestFlags.h>

NS_ASSUME_NONNULL_BEGIN

@class FBSDKGraphRequestConnection;
@protocol FBSDKGraphRequestConnecting;

typedef void (^FBSDKGraphRequestCompletion)(id<FBSDKGraphRequestConnecting> _Nullable connection,
                                            id _Nullable result,
                                            NSError *_Nullable error);

typedef void (^FBSDKGraphRequestBlock)(FBSDKGraphRequestConnection *_Nullable connection,
                                       id _Nullable result,
                                       NSError *_Nullable error);

/// A protocol to describe anything that represents a graph request
NS_SWIFT_NAME(GraphRequestProtocol)
@protocol FBSDKGraphRequest

/**
  The request parameters.
 */
@property (nonatomic, copy) NSDictionary<NSString *, id> *parameters;

/**
  The access token string used by the request.
 */
@property (nonatomic, copy, readonly, nullable) NSString *tokenString;

/**
  The Graph API endpoint to use for the request, for example "me".
 */
@property (nonatomic, copy, readonly) NSString *graphPath;

/**
  The HTTPMethod to use for the request, for example "GET" or "POST".
 */
@property (nonatomic, copy, readonly) FBSDKHTTPMethod HTTPMethod;

/**
  The Graph API version to use (e.g., "v2.0")
 */
@property (nonatomic, copy, readonly) NSString *version;

/**
   The graph request flags to use
 */
@property (nonatomic, assign, readonly) FBSDKGraphRequestFlags flags;

/**
 Convenience property to determine if graph error recover is disabled
 */
@property (nonatomic, getter = isGraphErrorRecoveryDisabled) BOOL graphErrorRecoveryDisabled;

/**
  Convenience property to determine if the request has attachments
 */
@property (nonatomic, readonly) BOOL hasAttachments;

/**
  Starts a connection to the Graph API.
 @param completion The handler block to call when the request completes.
 */
- (id<FBSDKGraphRequestConnecting>)startWithCompletion:(nullable FBSDKGraphRequestCompletion)completion;

/**
  A formatted description of the graph request
 */
- (NSString *)formattedDescription;

@end

NS_ASSUME_NONNULL_END
