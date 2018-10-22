//
//  LLSearchDelegate.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 7/2/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LLSearch;
@class LLSearchResults;
@class LLMultiTermSearchResults;
@class LLPOI;

/**
 *  Delegate used to return the results of a search.
 */
@protocol LLSearchDelegate <NSObject>

@optional

/**
 *  This method is called once new search results have been returned by the search object.
 *
 *  @param search  the search object
 *  @param searchResults the results of the search
 */
- (void)search:(LLSearch *)search results:(LLSearchResults *)searchResults;

/**
 *  This method is called once new search results have been returned by the search object.
 *
 *  @param search  the search object
 *  @param searchResults the results of the search
 */
- (void)search:(LLSearch *)search multiTermSearchResults:(LLMultiTermSearchResults *)searchResults;

/**
 *  The results of an autocomplete request.  Returns a list of suggestioned completetions for the given autocomplete string.
 *
 *  @param search        the search object
 *  @param query         the autocomplete string
 *  @param completetions an array of possble completetions
 */
- (void)search:(LLSearch *)search autocomplete:(NSString *)query completetions:(NSArray *)completetions;

/**
 *  The results of a proximity search request.  Returns a list of suggestioned POIs near the given lat/lng and floor.
 *
 *  @param search        the search object
 *  @param searchResults the results of the search
 */
- (void)proximitySearch:(LLSearch *)search results:(LLSearchResults *)searchResults;

/**
 *  The results of a proximity search with terms request.  Returns a list of suggestioned POIs near the given lat/lng and floor.
 *
 *  @param search        the search object
 *  @param searchResults the results of the search
 */
- (void)proximitySearchWithTerms:(LLSearch *)search results:(LLSearchResults *)searchResults;

/**
 *  The results of a search with terms request.  Returns a list of suggestioned POIs with the given terms.
 *
 *  @param search        the search object
 *  @param searchResults the results of the search
 */
- (void)searchWithTerms:(LLSearch *)search results:(LLSearchResults *)searchResults;

@end
