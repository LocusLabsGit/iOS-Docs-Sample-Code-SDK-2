//
//  LLAirline.h
//  LocusLabsSDK
//
//  Created by Sam Ziegler on 11/2/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface LLAirline : NSObject

+ (LLAirline *)oceanicAirlines;

@property (strong) NSString *name;
@property (strong) UIImage *smallLogo;

@end