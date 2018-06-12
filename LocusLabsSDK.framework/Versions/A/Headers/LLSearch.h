//
//  LLSearch.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 7/2/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "LLSearchDelegate.h"


/**
 *  Provides access to the LocusLabs POI search functionality.  This calls should not be created directly, but via the LLAiport search: function.
 */
@interface LLSearch : NSObject

/**
 *  The delegate to be notified when new search results are available.
 */
@property (nonatomic, weak) id<LLSearchDelegate> delegate;

/**
 *  Indicates whether a search is currently active.
 */
@property (nonatomic) BOOL searchInProgress;

/**
 *  Search the database for the given search string.  To search for a gate,
 *  prefix the gate with "gate:", such as "gate:D16".  To search a category use the "category:" prefix, such
 *  as "category:services".  To search a tag use the "tag:" prefix, such as "tag:food".
 *
 *  @param query the query string
 */
- (void)search:(NSString *)query;

- (void)search:(NSString *)query completion:(void (^ __nonnull)(LLSearchResults *))completion;

/**
 *  Search the database for the set of POIs that meet all of the given terms.
 *
 *  @param queryTerms the query string
 */
- (void)multiTermSearch:(NSArray *)queryTerms;

/**
 *  Generates a list of possible complete queries given the partial query string.
 *
 *  @param query the query to autocomplete
 */
- (void)autocomplete:(NSString *)query;

/**
 *  Generates a list POIs that are near the given lat/lng for the floor.
 */
- (void)proximitySearch:(NSString *)floorId lat:(NSNumber*)lat lng:(NSNumber*)lng;


/**
 *  Generates a list POIs that are near the given lat/lng for the floor and have the given term.
 */
- (void)proximitySearchWithTerms:(NSArray*)terms floorId:(NSString *)floorId lat:(NSNumber*)lat lng:(NSNumber*)lng;

/**
 *  Generates a list POIs that have any of the given terms.
 */
- (void)searchWithTerms:(NSArray*)terms;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end