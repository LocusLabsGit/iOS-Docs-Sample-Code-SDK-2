//
//  LLSearchResult.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 7/11/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LLPOIDataProtocol.h"

@class LLPosition;

/**
 *  A single search result.
 */
@interface LLSearchResult : NSObject <LLPOIData>

/**
 *  The unique identifier for the found POI.  This can be used to access additional data about the POI with
 *  through LLPOIDatabase.
 */
@property (nonatomic, strong, readonly) NSString *poiId;

/**
 *  A localized name of the POI which can be used for display purposes.
 */
@property (nonatomic, strong, readonly) NSString *name;

/**
 *  The geographic position of this POI.
 */
@property (nonatomic, strong, readonly) LLPosition *position;

/**
 *  The gate which is near the POI.
 */
@property (nonatomic, strong, readonly) NSString *gate;

/**
 *  The terminal which is near the POI.
 */
@property (nonatomic, strong, readonly) NSString *terminal;

@end
