//
//  LLPolyline.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 6/12/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "LLOverlay.h"

@class LLPath;

/**
 *  Creates multi-segment line with two or more verticies.
 */
@interface LLPolyline : LLOverlay

// redeclare floorId from overlay Internal header, so we can access it here as a property too (but it's @dynamic)
/**
 *  The FloorId for this marker.
 */
@property (nonatomic, strong) NSString *floorId;

/**
 *  The path associated with this LLPolyline
 */
@property (nonatomic, strong) LLPath *path;

/**
 *  The stroke width of this polyline.
 */
@property (nonatomic) CGFloat strokeWidth;

/**
 *  Stroke color of this polyline.
 */
@property (nonatomic, strong) UIColor *strokeColor;

@end
