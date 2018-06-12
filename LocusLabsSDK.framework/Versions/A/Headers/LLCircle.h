//
// Created by Rafal Hotlos on 06/03/2018.
// Copyright (c) 2018 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "LLOverlay.h"

@class LLLatLng;
@class LLPosition;


/**
 *  Draws a circle on an a LLMapView.
 */
@interface LLCircle : LLOverlay

/**
 *  Create a circle with the given radius and center. (**deprecated**)
 *
 *  @param center the center point of the circle
 *  @param radius the radius of the circle
 *
 *  @return the new circle object
 *
 *  **Deprecated**: use position instead of initiating with center
 */
+ (LLCircle *)circleWithCenter:(LLLatLng *)center radius:(NSNumber *)radius __attribute__((deprecated("use position instead of initiating with center")));

/**
 *  The current center of the circle. [**deprecated**]
 *
 *  **Deprecated**: use position
 */
@property (nonatomic, strong) LLLatLng *center __attribute__((deprecated("use position")));

/**
 *  The position of this circle center.
 */
@property (nonatomic, strong) LLPosition *position;

/**
 *  The current radius of the circle. Must be positive.
 *
 *  The default value is `0`.
 */
@property (nonatomic, strong) NSNumber *radius;

/**
 *  Set the fill color of this circle.
 *
 *  The default value is `nil`, resulting in no fill.
 */
@property (nonatomic, strong) UIColor *fillColor;

/**
 *  Set the stroke width of this circle.
 *  Setting strokeWidth to 0 results in no stroke.
 *
 *  The default value is `1`.
 */
@property (nonatomic) CGFloat strokeWidth;

/**
 *  Set the stroke color of this circle.
 *
 *  The default value is `black`.
 */
@property (nonatomic, strong) UIColor *strokeColor;

@end