//
//  LLBeaconDetection.h
//
//  Created by Glenn Dierkes on 9/18/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface LLBeaconDetection : NSObject

+ (LLBeaconDetection*)startMonitor;
+ (LLBeaconDetection*)startMonitor:(NSString*)status;
+ (void)stopMonitor;


@end

