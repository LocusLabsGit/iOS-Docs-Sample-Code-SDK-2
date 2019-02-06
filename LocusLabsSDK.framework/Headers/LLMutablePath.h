//
//  LLMutablePath.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 6/26/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LLPath.h"

@class LLLatLng;

/**
 * Mutable subclass of LLPath. This class is **deprecated** as the LLPath is mutable.
 */
__attribute__((deprecated("use LLPath, it's mutable")))
@interface LLMutablePath : LLPath

@end