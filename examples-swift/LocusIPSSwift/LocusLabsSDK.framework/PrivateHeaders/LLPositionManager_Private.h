//
// Created by Rafal Hotlos on 09/10/2019.
// Copyright (c) 2019 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocusLabsSDK/LLPositionManager.h>

@class LLBeaconsPositioning;

@interface LLPositionManager () <CLLocationManagerDelegate>

- (CLLocationManager *)locationManager;

+ (void) requestLocationPermissionFromUser:(CLLocationManager*)locationManager;

@end
