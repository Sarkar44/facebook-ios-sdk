/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <Foundation/Foundation.h>

#import "FBSDKAppEventUserDataType.h"

NS_ASSUME_NONNULL_BEGIN

/*
 Describes a type that can persist user data
 */
NS_SWIFT_NAME(UserDataPersisting)
@protocol FBSDKUserDataPersisting

- (void)setUserEmail:(nullable NSString *)email
           firstName:(nullable NSString *)firstName
            lastName:(nullable NSString *)lastName
               phone:(nullable NSString *)phone
         dateOfBirth:(nullable NSString *)dateOfBirth
              gender:(nullable NSString *)gender
                city:(nullable NSString *)city
               state:(nullable NSString *)state
                 zip:(nullable NSString *)zip
             country:(nullable NSString *)country
          externalId:(nullable NSString *)externalId
NS_SWIFT_NAME(setUser(email:firstName:lastName:phone:dateOfBirth:gender:city:state:zip:country:externalId:));

- (nullable NSString *)getUserData;

- (void)clearUserData;

- (void)setUserData:(nullable NSString *)data
            forType:(FBSDKAppEventUserDataType)type;

- (void)clearUserDataForType:(FBSDKAppEventUserDataType)type;

@end

NS_ASSUME_NONNULL_END
