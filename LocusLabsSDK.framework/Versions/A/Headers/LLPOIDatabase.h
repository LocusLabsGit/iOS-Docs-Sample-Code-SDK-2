//
//  LLPOIDatabase.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 7/2/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "LLPOIDatabaseDelegate.h"

typedef void (^PoisLoadedBlock) (NSArray *pois);

/**
 *  Provides access to the LocusLabs POI database.  Objects not be created directly, but via the LLVenue poiDatabase method
 */
@interface LLPOIDatabase : NSObject

@property (nonatomic, weak) id<LLPOIDatabaseDelegate> delegate;

/**
 *  Load data about a specific POI.
 *
 *  @param poiId the POI to load
 */
- (void)loadPOI:(NSString *)poiId;

- (void)loadPOI:(NSString *)poiId completion:(void (^)(LLPOI *poi))completion;

/**
 *  Load data about the poiIds passed in
 *
 *  @param poiIds - an array of poiIds
 *  @param block - the block to callback to
 */
- (void)loadPois:(NSArray*)poiIds withBlock:(PoisLoadedBlock)block;

/**
 *  Load data about ALL POI's for this venue
 *
 *  @param block the block to callback to
 */
- (void)loadAllPois:(PoisLoadedBlock)block;

@end
