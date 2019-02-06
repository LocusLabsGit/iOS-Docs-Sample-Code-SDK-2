//
//  LLPOIDatabaseDelegate.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 7/2/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LLPOIDatabase;
@class LLPOI;

/**
 *  Delegate for the LLPOIDatabase class.
 */
@protocol LLPOIDatabaseDelegate <NSObject>

@optional

/**
 *  Returns a POI loadd via the LLPOIDatabase loadPOI: method.
 *
 *  @param poiDatabase the database which generated the call
 *  @param poi         the resulting POI
 */
- (void)poiDatabase:(LLPOIDatabase *)poiDatabase poiLoaded:(LLPOI *)poi;

@end