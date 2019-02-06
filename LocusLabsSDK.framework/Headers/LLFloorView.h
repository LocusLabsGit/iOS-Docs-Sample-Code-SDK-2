//
//  LLFloorView.h
//  LocusLabsSDK
//
//  Created by Glenn Dierkes on 9/12/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "LLMapView.h"

/**
 * This class is **deprecated** as the usage of floorId is recommended.
 */
__attribute__((deprecated("use floorId for overlays")))
@interface LLFloorView : NSObject

@property (nonatomic, weak) LLMapView* mapView;
@property (nonatomic, strong) NSString *floorId;

@end