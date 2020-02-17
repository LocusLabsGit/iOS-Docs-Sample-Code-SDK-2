//
//  LLMap.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 6/17/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>


@class LLLatLng;
@class LLPosition;

@interface LLMap : NSObject

@property(nonatomic, strong) NSNumber *radius;
@property(nonatomic, strong) LLLatLng *center __attribute__((deprecated("use centerPosition instead")));;
@property(nonatomic, strong) LLPosition *centerPosition;
@property(nonatomic, strong) NSNumber *heading;
@property(nonatomic, readonly) NSString *venueId;
@property(nonatomic, readonly) NSString *buildingId;
@property(nonatomic, strong) NSString *floorId;

/**
 * Returns the ordinal associated with the given floorId.
 */
- (NSNumber *)getOrdinalForFloorId:(NSString *)floorId;

- (void)zoomToExtentOfPositions:(NSArray *)positions;

@end