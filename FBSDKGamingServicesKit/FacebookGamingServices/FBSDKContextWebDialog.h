/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "TargetConditionals.h"

#import <Foundation/Foundation.h>
#import <FBSDKCoreKit/FBSDKCoreKit.h>
#import <FacebookGamingServices/FBSDKDialogProtocol.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Context web dialog for the all context api dialogs executed in a browser
 */
NS_SWIFT_NAME(ContextWebDialog)
@interface FBSDKContextWebDialog : NSObject <FBSDKWebDialogDelegate, FBSDKDialog>

/**
 The current web dialog that shows the web content
*/
@property (nonatomic, strong, nullable) FBSDKWebDialog* currentWebDialog;

+ (instancetype)new NS_UNAVAILABLE;

/**
 Initializer to be used by subclasses.
 */
- (instancetype)initWithDelegate:(id<FBSDKContextDialogDelegate>)delegate
NS_SWIFT_NAME(init(delegate:));

/**
 Depending on the content size within the browser, this method allows for the resizing of web dialog
*/
- (CGRect)createWebDialogFrameWithWidth:(CGFloat)width height:(CGFloat)height windowFinder:(id<FBSDKWindowFinding>)windowFinder;

@end
NS_ASSUME_NONNULL_END
