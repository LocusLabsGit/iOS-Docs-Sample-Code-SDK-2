//
// Created by Rafal Hotlos on 30/03/2018.
// Copyright (c) 2018 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LLPosition.h"

@class LLLatLng;

/**
 *  A waypoint along a navigation path.
 */
@interface LLWaypoint : LLPosition

/**
 *  The distance, in meters, this waypoint is from the previous one.
 */
@property (nonatomic, readonly) NSNumber *distance;

/**
 *  The estimated time, in minutes, to travel from the previous waypoint to this one.
 */
@property (nonatomic, readonly) NSNumber *eta;

/**
 *  A boolean flag which is true if this waypoint was specified as a destination.
 */
@property (nonatomic, readonly) NSNumber *isDestination;

/**
 *  A boolean flag which is true if this waypoint was specified as a portal.
 */
@property (nonatomic, readonly) NSNumber *isPortal;

/**
 *  The portal type.
 */
@property (nonatomic, readonly) NSString *portalType;

/**
 *  The details.
 */
@property (nonatomic, readonly) NSString *details;

/**
 *  The action.
 */
@property (nonatomic, readonly) NSString *action;

/**
 *  The difference between levels from the previous waypoint to this one.
 */
@property (nonatomic, readonly) NSNumber *levelDifference;

/**
 *  A specific path to use to get to the next waypoint.
 */
@property (nonatomic, readonly) NSArray *curvePath;

/**
 * Does the waypoint go through a "securityCheckpoint".
 */
@property (nonatomic, readonly) NSNumber *securityCheckpoint;

/**
 * LatLng
 */
@property (nonatomic, readonly) LLLatLng *latLng;

/**
 *  The floorId.
 */
@property (nonatomic, readonly) NSString *floorId;

@end
