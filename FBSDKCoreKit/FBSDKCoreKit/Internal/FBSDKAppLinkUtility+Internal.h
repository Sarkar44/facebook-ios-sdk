/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#if !TARGET_OS_TV

 #import <Foundation/Foundation.h>

 #import "FBSDKAppLinkUtility.h"

NS_ASSUME_NONNULL_BEGIN

@protocol FBSDKInfoDictionaryProviding;
@protocol FBSDKAppEventDropDetermining;
@protocol FBSDKAppEventParametersExtracting;
@protocol FBSDKGraphRequestFactory;
@protocol FBSDKSettings;
@protocol FBSDKAppEventsConfigurationProviding;
@protocol FBSDKAdvertiserIDProviding;
@protocol FBSDKAppLinkURLCreating;

@interface FBSDKAppLinkUtility (Internal)

@property (class, nullable, nonatomic) id<FBSDKGraphRequestFactory> graphRequestFactory;
@property (class, nullable, nonatomic) id<FBSDKInfoDictionaryProviding> infoDictionaryProvider;
@property (class, nullable, nonatomic) id<FBSDKSettings> settings;
@property (class, nullable, nonatomic) id<FBSDKAppEventsConfigurationProviding> appEventsConfigurationProvider;
@property (class, nullable, nonatomic) id<FBSDKAdvertiserIDProviding> advertiserIDProvider;
@property (class, nullable, nonatomic) id<FBSDKAppEventDropDetermining> appEventsDropDeterminer;
@property (class, nullable, nonatomic) id<FBSDKAppEventParametersExtracting> appEventParametersExtractor;
@property (class, nullable, nonatomic) id<FBSDKAppLinkURLCreating> appLinkURLFactory;


+ (void)configureWithGraphRequestFactory:(id<FBSDKGraphRequestFactory>)graphRequestFactory
                  infoDictionaryProvider:(id<FBSDKInfoDictionaryProviding>)infoDictionaryProvider
                                settings:(id<FBSDKSettings>)settings
          appEventsConfigurationProvider:(id<FBSDKAppEventsConfigurationProviding>)appEventsConfigurationProvider
                    advertiserIDProvider:(id<FBSDKAdvertiserIDProviding>)advertiserIDProvider
                 appEventsDropDeterminer:(id<FBSDKAppEventDropDetermining>)appEventsDropDeterminer
             appEventParametersExtractor:(id<FBSDKAppEventParametersExtracting>)appEventParametersExtractor
                       appLinkURLFactory:(id<FBSDKAppLinkURLCreating>)appLinkURLFactory
NS_SWIFT_NAME(configure(graphRequestFactory:infoDictionaryProvider:settings:appEventsConfigurationProvider:advertiserIDProvider:appEventsDropDeterminer:appEventParametersExtractor:appLinkURLFactory:));

@end

NS_ASSUME_NONNULL_END

#endif
