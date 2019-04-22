//
//  CursusBeaconContoller.h
//  CursusLibrary
//
//  Created by Sky on 1/14/16.
//  Copyright © 2016 Cursus. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CursusBeaconItem.h"
@import CoreLocation;

@interface CursusBeaconContoller : NSObject <CLLocationManagerDelegate>

@property (strong, nonatomic) CLLocationManager *locationManager;
@property (strong, nonatomic) NSMutableArray *items;
@property (strong, nonatomic) CursusBeaconItem *lastSeenBeaconItem;
@property (strong, nonatomic) NSDate *lastUpdateBeaconTime;
@property (nonatomic) BOOL bEnableiBeaconRegion;
@property (nonatomic) BOOL bProximityFar;
@property (nonatomic) BOOL bProximityNear;
@property (nonatomic) BOOL bProximityImmediate;
@property (nonatomic) BOOL bGeoLoggingEnabled;
@property (nonatomic) NSTimeInterval iBeaconsAlertCushionSeconds;
@property (nonatomic) int iAccuracyCtr;
@property (nonatomic) int iBeaconsAccuracyMin;

-(void)startMonitoringItems;
-(void)stopClearMonitoringItems;
-(void)addtarget:(id)target action:(SEL)method;

@end
