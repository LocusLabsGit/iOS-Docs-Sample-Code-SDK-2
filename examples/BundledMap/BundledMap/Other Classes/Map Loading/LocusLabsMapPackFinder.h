//
//  LocusLabsMapPackFinder.h
//  RecommendedImplementation
//
//  Created by Sam Ziegler on 7/12/15.
//  Copyright (c) 2015 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface LocusLabsMapPackFinder : NSObject

@property (strong,nonatomic,readonly) NSString *directory;

+ (LocusLabsMapPackFinder *)mapPackFinder;
+ (LocusLabsMapPackFinder *)mapPackFinderWithDirectory:(NSString *)directory;
+ (NSString *)mapPackFilenamePattern;

- (id)initWithDirectory:(NSString *)directory;

- (NSArray *)mapPackPaths;
- (NSString *)newestMapPackPath;

@end

