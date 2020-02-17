//
//  LLMarker.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 7/9/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LLOverlay.h"

@class LLPoint;
@class LLPosition;

/**
 *  Used for placing images markers on a map.
 */
@interface LLMarker : LLOverlay

/**
 *  The image coordinates which is centered on the position.
 */
@property (nonatomic, strong) LLPoint *anchor;

/**
 *  The URL of the image icon to use for this marker.
 */
@property (nonatomic, strong) NSString *iconUrl;

/**
 *  The position of this marker on the map.
 *  @warning This property was of type `LLLatLng` in SDK 1.6, but it's now LLPosition. Providing LLLatLng is still supported
 *  for compatibility with 1.6, but it's **deprecated** and will be removed in future releases.
 */
@property (nonatomic, strong) id position;

// redeclare floorId from overlay Internal header, so we can access it here as a property too (but it's @dynamic)
/**
 *  The FloorId for this marker.
 *
 *  **Deprecated**: use position
 */
@property (nonatomic, strong) NSString *floorId __attribute__((deprecated("use position")));;

/**
 * Additional data for the marker.
 */
@property (nonatomic, strong) id userData;

// TODO [api] mark as removed
//@property (assign,nonatomic) BOOL draggable;


/**
 * The opacity of this marker.
 */
@property (nonatomic, strong) NSNumber *opacity;

/**
 * The highest scale factor that will be applied to the marker based on the zoom level.
 */
@property (nonatomic, strong) NSNumber *maxScale;

/**
 * The smallest scale factor that will be applied to the marker based on the zoom level.
 */
@property (nonatomic,strong) NSNumber *minScale;

@end