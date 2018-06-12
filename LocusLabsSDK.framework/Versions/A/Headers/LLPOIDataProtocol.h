//
//  LLPOIDataProtocol.h
//  LocusLabsSDK
//
//  Created by Christopher Griffith on 1/31/17.
//  Copyright © 2017 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LLPosition;

@protocol LLPOIData <NSObject>

@property (strong,nonatomic) NSString *poiId;
@property (strong,nonatomic) NSString *name;
@property (strong,nonatomic) LLPosition *position;
@property (strong,nonatomic) NSString *gate;
@property (strong,nonatomic) NSString *terminal;

@end
