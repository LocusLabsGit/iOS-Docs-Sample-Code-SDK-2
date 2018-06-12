//
// Created by Jeff Goldberg on 6/12/15.
// Copyright (c) 2015 iBeaconModules.us. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LLPositionManager;

@interface LLPositionManagerRollingCarpetRegionAlgorithm : NSObject

- (instancetype)initWithPositionManager:(LLPositionManager *)positionManager venueDataParameters:(NSDictionary *)parameters;

@end