//
//  CursusBeaconItem.h
//  CursusLibrary
//
//  Created by Sky on 1/14/16.
//  Copyright © 2016 Cursus. All rights reserved.
//

#import <Foundation/Foundation.h>
@import CoreLocation;

@interface CursusBeaconItem : NSObject <NSCoding>

@property (strong, nonatomic, readonly) NSString *name;
@property (strong, nonatomic, readonly) NSUUID *uuid;
@property (assign, nonatomic, readonly) CLBeaconMajorValue majorValue;
@property (assign, nonatomic, readonly) CLBeaconMinorValue minorValue;
@property (strong, nonatomic) NSString *latitude;
@property (strong, nonatomic) NSString *longitude;
@property (strong, nonatomic) NSString *airportIdent;
@property (strong, nonatomic) CLBeacon *lastSeenBeacon;

- (instancetype)initWithName:(NSString *)name
                        uuid:(NSUUID *)uuid
                       major:(CLBeaconMajorValue)major
                       minor:(CLBeaconMinorValue)minor
                airportIdent:(NSString*)airportIdent
                    latitude:(NSString*)latitude
                   longitude:(NSString*)longitude;

- (BOOL)isEqualToCLBeacon:(CLBeacon *)beacon;


@end
