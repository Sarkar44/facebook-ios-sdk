/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
  A container class for data attachments so that additional metadata can be provided about the attachment.
 */
NS_SWIFT_NAME(GraphRequestDataAttachment)
@interface FBSDKGraphRequestDataAttachment : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
  Initializes the receiver with the attachment data and metadata.
 @param data The attachment data (retained, not copied)
 @param filename The filename for the attachment
 @param contentType The content type for the attachment
 */
- (instancetype)initWithData:(NSData *)data
                    filename:(NSString *)filename
                 contentType:(NSString *)contentType
NS_DESIGNATED_INITIALIZER;

/**
  The content type for the attachment.
 */
@property (nonatomic, copy, readonly) NSString *contentType;

/**
  The attachment data.
 */
@property (nonatomic, strong, readonly) NSData *data;

/**
  The filename for the attachment.
 */
@property (nonatomic, copy, readonly) NSString *filename;

@end

NS_ASSUME_NONNULL_END
