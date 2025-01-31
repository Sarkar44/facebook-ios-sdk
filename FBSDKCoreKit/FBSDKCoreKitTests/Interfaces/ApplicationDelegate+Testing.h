/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "FBSDKApplicationDelegate.h"

NS_ASSUME_NONNULL_BEGIN

@protocol FBSDKSettingsLogging;
@protocol FBSDKAccessTokenProviding;
@protocol FBSDKAuthenticationTokenProviding;
@protocol FBSDKAuthenticationTokenSetting;
@protocol FBSDKBackgroundEventLogging;
@protocol FBSDKEventLogging;
@protocol FBSDKFeatureChecking;
@protocol FBSDKNotificationObserving;
@protocol FBSDKApplicationLifecycleObserving;
@protocol FBSDKApplicationActivating;
@protocol FBSDKApplicationStateSetting;
@protocol FBSDKAppEventsConfiguring;
@protocol FBSDKServerConfigurationProviding;
@protocol FBSDKSourceApplicationTracking;
@protocol FBSDKProfileProviding;
@protocol FBSDKDataPersisting;
@protocol FBSDKPaymentObserving;
@class FBSDKAccessTokenExpirer;

@interface FBSDKApplicationDelegate (Testing)

@property (nonatomic, assign) id<FBSDKNotificationObserving> notificationObserver;
@property (nonatomic, nullable) Class<FBSDKAccessTokenProviding, FBSDKAccessTokenSetting> tokenWallet;
@property (nonatomic, readonly, nonnull) id<FBSDKFeatureChecking> featureChecker;
@property (nonnull, nonatomic, readonly) id<FBSDKSourceApplicationTracking, FBSDKAppEventsConfiguring, FBSDKApplicationLifecycleObserving, FBSDKApplicationActivating, FBSDKApplicationStateSetting, FBSDKEventLogging> appEvents;
@property (nonnull, nonatomic, readonly) id<FBSDKServerConfigurationProviding> serverConfigurationProvider;
@property (nonnull, nonatomic, readonly) id<FBSDKDataPersisting> store;
@property (nonnull, nonatomic, readonly) Class<FBSDKAuthenticationTokenProviding, FBSDKAuthenticationTokenSetting> authenticationTokenWallet;
@property (nonnull, nonatomic, readonly) Class<FBSDKProfileProviding> profileProvider;
@property (nonnull, nonatomic, readonly) id<FBSDKBackgroundEventLogging> backgroundEventLogger;
@property (nonnull, nonatomic, readonly) id<FBSDKSettingsLogging> settings;
@property (nonnull, nonatomic) NSHashTable<id<FBSDKApplicationObserving>> *applicationObservers;
@property (nonnull, nonatomic, readonly) FBSDKAccessTokenExpirer *accessTokenExpirer;
@property (nonnull, nonatomic, readonly) id<FBSDKPaymentObserving> paymentObserver;

+ (void)resetHasInitializeBeenCalled
NS_SWIFT_NAME(reset());

- (instancetype)initWithNotificationCenter:(id<FBSDKNotificationObserving>)observer
                               tokenWallet:(Class<FBSDKAccessTokenProviding, FBSDKAccessTokenSetting>)tokenWallet
                                  settings:(id<FBSDKSettingsLogging>)settings
                            featureChecker:(id<FBSDKFeatureChecking>)featureChecker
                                 appEvents:(id<FBSDKSourceApplicationTracking, FBSDKAppEventsConfiguring, FBSDKApplicationLifecycleObserving, FBSDKApplicationActivating, FBSDKApplicationStateSetting, FBSDKEventLogging>)appEvents
               serverConfigurationProvider:(id<FBSDKServerConfigurationProviding>)serverConfigurationProvider
                                     store:(id<FBSDKDataPersisting>)store
                 authenticationTokenWallet:(Class<FBSDKAuthenticationTokenProviding, FBSDKAuthenticationTokenSetting>)authenticationTokenWallet
                           profileProvider:(Class<FBSDKProfileProviding>)profileProvider
                     backgroundEventLogger:(id<FBSDKBackgroundEventLogging>)backgroundEventLogger
                           paymentObserver:(id<FBSDKPaymentObserving>)paymentObserver;
- (void)initializeSDKWithLaunchOptions:(NSDictionary<UIApplicationLaunchOptionsKey, id> *)launchOptions;
- (void)applicationDidEnterBackground:(NSNotification *)notification;
- (void)applicationDidBecomeActive:(NSNotification *)notification;
- (void)applicationWillResignActive:(NSNotification *)notification;
- (void)_logSDKInitialize;

@end

NS_ASSUME_NONNULL_END
