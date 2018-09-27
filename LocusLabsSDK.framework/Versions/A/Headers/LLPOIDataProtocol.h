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

@property (nonatomic, readonly) NSString *poiId;
@property (nonatomic, readonly) NSString *name;
@property (nonatomic, readonly) LLPosition *position;
@property (nonatomic, readonly) NSString *gate;
@property (nonatomic, readonly) NSString *terminal;

@end
