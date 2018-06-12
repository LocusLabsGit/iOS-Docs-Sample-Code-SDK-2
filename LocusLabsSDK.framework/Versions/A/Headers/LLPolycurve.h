//
//  LLPolycurve.h
//  LocusLabsSDK
//
//  Created by Glenn Dierkes on 1/12/15.
//  Copyright (c) 2015 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "LLCurvedPath.h"
#import "LLOverlay.h"

/**
 *  Creates Bezier curves overlay
 */
@interface LLPolycurve : LLOverlay

// redeclare floorId from overlay Internal header, so we can access it here as a property too (but it's @dynamic)
/**
 *  The FloorId for this marker.
 */
@property (nonatomic, strong) NSString *floorId;

/**
 *  The path associated with this LLPolyline
 */
@property (nonatomic, strong) LLCurvedPath *curvedPath;

/**
 *  The stroke width of this polyline.
 */
@property (nonatomic) CGFloat strokeWidth;

/**
 *  Stroke color of this polyline.
 */
@property (nonatomic, strong) UIColor *strokeColor;

/**
 *  Set the icons used along this polyline.
 *
 *  @param icons
 */
// TODO [api] marked as removed in the docs (migrating from 1.6 to 2.0)
//- (void)setIcons:(NSArray *)icons;

@end