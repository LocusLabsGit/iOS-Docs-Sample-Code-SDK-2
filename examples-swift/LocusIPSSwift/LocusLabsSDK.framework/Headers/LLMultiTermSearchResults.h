//
//  LLMultiTermSearchResults.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 7/11/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface LLMultiTermSearchResults : NSObject

/**
 *  The current search results.
 */
@property (strong,readonly) NSArray *results;

/**
 *  The current search other results.
 */
@property (strong,readonly) NSArray *otherResults;

/**
 *  The query terms array.
 */
@property (strong,readonly) NSArray *queryTerms;

/**
 *  Whether additional results are available.  If there are, they can be retrieved by another call to search.
 *
 *  @return the more flag
 */
- (BOOL)hasMore;

@end