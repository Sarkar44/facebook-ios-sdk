/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "FBSDKError.h"

#import <FBSDKCoreKit_Basics/FBSDKCoreKit_Basics.h>

#import "FBSDKConstants.h"
#import "FBSDKErrorFactory.h"
#import "FBSDKErrorReporting.h"
#import "FBSDKFeatureManager.h"
#import "FBSDKNetworkErrorChecker.h"

@interface FBSDKError ()

@property (class, nullable, nonatomic) id<FBSDKErrorReporting> errorReporter;

@end

@implementation FBSDKError

// MARK: - Class Dependencies

static id<FBSDKErrorReporting> _errorReporter;

+ (id<FBSDKErrorReporting>)errorReporter
{
  return _errorReporter;
}

+ (void)setErrorReporter:(id<FBSDKErrorReporting>)errorReporter
{
  _errorReporter = errorReporter;
}

+ (void)configureWithErrorReporter:(id<FBSDKErrorReporting>)errorReporter
{
  self.errorReporter = errorReporter;
}

#if DEBUG && FBTEST

+ (void)reset
{
  _errorReporter = nil;
}

#endif

// MARK: - General Errors

+ (NSError *)errorWithCode:(NSInteger)code message:(nullable NSString *)message
{
  return [self errorWithCode:code message:message underlyingError:nil];
}

+ (NSError *)errorWithDomain:(NSErrorDomain)domain code:(NSInteger)code message:(nullable NSString *)message
{
  return [self errorWithDomain:domain code:code message:message underlyingError:nil];
}

+ (NSError *)errorWithCode:(NSInteger)code
                   message:(nullable NSString *)message
           underlyingError:(nullable NSError *)underlyingError
{
  return [self errorWithCode:code userInfo:@{} message:message underlyingError:underlyingError];
}

+ (NSError *)errorWithDomain:(NSErrorDomain)domain
                        code:(NSInteger)code
                     message:(nullable NSString *)message
             underlyingError:(nullable NSError *)underlyingError
{
  return [self errorWithDomain:domain code:code userInfo:@{} message:message underlyingError:underlyingError];
}

+ (NSError *)errorWithCode:(NSInteger)code
                  userInfo:(NSDictionary<NSErrorUserInfoKey, id> *)userInfo
                   message:(NSString *)message
           underlyingError:(NSError *)underlyingError
{
  return [self errorWithDomain:FBSDKErrorDomain
                          code:code
                      userInfo:userInfo
                       message:message
               underlyingError:underlyingError];
}

+ (NSError *)errorWithDomain:(NSErrorDomain)domain
                        code:(NSInteger)code
                    userInfo:(nullable NSDictionary<NSErrorUserInfoKey, id> *)userInfo
                     message:(nullable NSString *)message
             underlyingError:(nullable NSError *)underlyingError
{
  FBSDKErrorFactory *factory = [[FBSDKErrorFactory alloc] initWithReporter:self.errorReporter];
  return [factory errorWithDomain:domain
                             code:code
                         userInfo:userInfo
                          message:message
                  underlyingError:underlyingError];
}

+ (NSError *)invalidArgumentErrorWithName:(NSString *)name
                                    value:(nullable id)value
                                  message:(nullable NSString *)message
{
  return [self invalidArgumentErrorWithName:name value:value message:message underlyingError:nil];
}

+ (NSError *)invalidArgumentErrorWithDomain:(NSErrorDomain)domain
                                       name:(NSString *)name
                                      value:(nullable id)value
                                    message:(nullable NSString *)message
{
  return [self invalidArgumentErrorWithDomain:domain name:name value:value message:message underlyingError:nil];
}

+ (NSError *)invalidArgumentErrorWithName:(NSString *)name
                                    value:(id)value
                                  message:(NSString *)message
                          underlyingError:(NSError *)underlyingError
{
  return [self invalidArgumentErrorWithDomain:FBSDKErrorDomain
                                         name:name
                                        value:value
                                      message:message
                              underlyingError:underlyingError];
}

+ (NSError *)invalidArgumentErrorWithDomain:(NSErrorDomain)domain
                                       name:(NSString *)name
                                      value:(nullable id)value
                                    message:(nullable NSString *)message
                            underlyingError:(nullable NSError *)underlyingError
{
  if (!message) {
    message = [[NSString alloc] initWithFormat:@"Invalid value for %@: %@", name, value];
  }
  NSMutableDictionary<NSString *, id> *userInfo = [NSMutableDictionary new];
  [FBSDKTypeUtility dictionary:userInfo setObject:name forKey:FBSDKErrorArgumentNameKey];
  [FBSDKTypeUtility dictionary:userInfo setObject:value forKey:FBSDKErrorArgumentValueKey];
  return [self errorWithDomain:domain
                          code:FBSDKErrorInvalidArgument
                      userInfo:userInfo
                       message:message
               underlyingError:underlyingError];
}

+ (NSError *)requiredArgumentErrorWithName:(NSString *)name message:(NSString *)message
{
  return [self requiredArgumentErrorWithName:name message:message underlyingError:nil];
}

+ (NSError *)requiredArgumentErrorWithDomain:(NSErrorDomain)domain
                                        name:(NSString *)name
                                     message:(nullable NSString *)message
{
  if (!message) {
    message = [[NSString alloc] initWithFormat:@"Value for %@ is required.", name];
  }
  return [self invalidArgumentErrorWithDomain:domain name:name value:nil message:message underlyingError:nil];
}

+ (NSError *)requiredArgumentErrorWithName:(NSString *)name
                                   message:(NSString *)message
                           underlyingError:(NSError *)underlyingError
{
  if (!message) {
    message = [[NSString alloc] initWithFormat:@"Value for %@ is required.", name];
  }
  return [self invalidArgumentErrorWithName:name value:nil message:message underlyingError:underlyingError];
}

+ (NSError *)unknownErrorWithMessage:(NSString *)message
{
  return [self errorWithCode:FBSDKErrorUnknown userInfo:@{} message:message underlyingError:nil];
}

// MARK: - Network Error Checking

+ (BOOL)isNetworkError:(NSError *)error
{
  FBSDKNetworkErrorChecker *checker = [FBSDKNetworkErrorChecker new];
  return [checker isNetworkError:error];
}

@end
