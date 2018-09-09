//
//  LocusLabsMapPackFinder.m
//  RecommendedImplementation
//
//  Created by Sam Ziegler on 7/12/15.
//  Copyright (c) 2015 LocusLabs. All rights reserved.
//

#import "LocusLabsMapPackFinder.h"

#import "LocusLabsSDK/LocusLabsSDK.h"

@implementation LocusLabsMapPackFinder

+ (LocusLabsMapPackFinder *)mapPackFinder
{
    NSBundle *bundle = [NSBundle mainBundle];
    return [LocusLabsMapPackFinder mapPackFinderWithDirectory:bundle.resourcePath];
}

+ (LocusLabsMapPackFinder *)mapPackFinderWithDirectory:(NSString *)directory
{
    return [[LocusLabsMapPackFinder alloc] initWithDirectory:directory];
}

+ (NSString *)mapPackFilenamePattern
{
    return [NSString stringWithFormat:@"^ios-%@-([0-9:A-Z\\-]+).tar.gz$",[LLLocusLabs setup].accountId];
}

- (id)initWithDirectory:(NSString *)directory
{
    self = [super init];
    
    if (self) {
        _directory = directory;
    }
    
    return self;
}

- (NSArray *)mapPackPaths
{
    NSRegularExpression *mapPackRegex = [NSRegularExpression regularExpressionWithPattern:[LocusLabsMapPackFinder mapPackFilenamePattern] options:0 error:nil];
    NSMutableArray *mapPacks = [NSMutableArray array];
    NSArray *directoryContents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:self.directory error:nil];
    
    for (NSString *filename in directoryContents) {
        if ([mapPackRegex numberOfMatchesInString:filename options:0 range:NSMakeRange(0, filename.length)]) {
            NSString *path = [self.directory stringByAppendingPathComponent:filename];
            [mapPacks addObject:path];
        }
    }
    
    return mapPacks;
}

- (NSString *)newestMapPackPath
{
    
    NSString *newestMapPack;
    for (NSString *mapPack in self.mapPackPaths) {
        if (!newestMapPack) {
            newestMapPack = mapPack;
        }
        
        if ([newestMapPack compare:mapPack] == NSOrderedAscending){
            newestMapPack = mapPack;
        }
    }
    
    return newestMapPack;
}

@end
