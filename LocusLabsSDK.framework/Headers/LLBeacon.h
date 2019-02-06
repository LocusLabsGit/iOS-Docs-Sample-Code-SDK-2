//
//  LLBeaconInfo.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 6/18/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LLLatLng;

@interface LLBeacon : NSObject

- (instancetype)initWithUUID:(NSString *)uuid majorId:(NSNumber *)majorId minorId:(NSNumber *)minorId rssi:(NSNumber *)rssi;

@property (nonatomic, readonly) NSString *uuid;
@property (nonatomic, readonly) NSString *floorId;
@property (nonatomic, readonly) NSString *buildingId;
@property (nonatomic, readonly) NSString *venueId;
@property (nonatomic, readonly) NSNumber *majorId;
@property (nonatomic, readonly) NSNumber *minorId;
@property (nonatomic, readonly) NSNumber *rssi;
@property (nonatomic, readonly) LLLatLng *position;

@end
