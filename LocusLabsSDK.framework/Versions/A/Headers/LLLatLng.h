//
//  LLLatLng.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 6/18/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Represents a geographics position in latitude and longitude.
 */
@interface LLLatLng : NSObject

/**
 * Designated initializer
 * @param lat
 * @param lng
 * @return
 */
- (instancetype)initWithLat:(NSNumber *)lat lng:(NSNumber *)lng;

/**
 *  Latitude
 *
 *  @return latitude
 */
@property (nonatomic, readonly) NSNumber *lat;

/**
 *  Longitude
 *
 *  @return longitutde
 */
@property (nonatomic, readonly) NSNumber *lng;

/**
 *  Calculates the distance (in meters) between two LLLatLng objects
 *
 *  @param latLng the other LLLatLng
 *
 *  @return the distance (in meteres)
 */
- (NSNumber *)distance:(nonnull LLLatLng *)latLng;

/**
 *  Calculates the bearing between this position and another one.
 *
 *  @param latLng the other LLLatLng
 *
 *  @return the bearing (in radians)
 */
- (NSNumber *)bearing:(LLLatLng *)latLng;

/**
 *  Calculates the geohash for the Lat/Lng coordinates.
 *
 *  @return the geohash string
 */
@property (nonatomic, readonly) NSString *geohash;

@end