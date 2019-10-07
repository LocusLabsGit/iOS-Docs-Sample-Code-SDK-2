//
//  LLMapPackFinder.h
//  LocusLabsSDK
//
//  Created by Rafal Hotlos on 16/09/2019.
//  Copyright © 2019 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Provides methods to find and list available LLMapPack(s)
 */
@interface LLMapPackFinder : NSObject

/**
 * Map pack finder returning map packs from the app bundle
 */
+ (LLMapPackFinder *)mapPackFinder;
/**
 * Map pack finder returning map packs from given directory
 */
+ (LLMapPackFinder *)mapPackFinderWithDirectory:(NSString *)directory;
/**
 * Init map pack finder with given directory
 */
- (id)initWithDirectory:(NSString *)directory;

/**
 * The pattern for matching map pack file names
 */
+ (NSString *)mapPackFilenamePattern;

/**
 * The directory in which this map pack finder searches for map packs;
 */
@property (strong, nonatomic, readonly) NSString *directory;

/**
 * Map pack paths found by this map pack finder.
 */
- (NSArray *)mapPackPaths;

/**
 * The newest map pack found by this map pack finder.
 */
- (NSString *)newestMapPackPath;

@end
