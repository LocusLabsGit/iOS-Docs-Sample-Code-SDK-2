//
//  LocusLabsMapPack.m
//  RecommendedImplementation
//
//  Created by Sam Ziegler on 7/12/15.
//  Copyright (c) 2015 LocusLabs. All rights reserved.
//

#import "LocusLabsMapPack.h"
#import "LocusLabsCache.h"
#import "LocusLabsMapPackFinder.h"

#import "LocusLabsSDK/LocusLabsSDK.h"
#import "NVHTarGzip.h"

@implementation LocusLabsMapPack

+ (LocusLabsMapPack *)mapPackNewestAvailable
{
    LocusLabsMapPackFinder *mapPackFinder = [LocusLabsMapPackFinder mapPackFinder];
    
    return [LocusLabsMapPack mapPackNewestAvailableWithFinder:mapPackFinder];
}

+ (LocusLabsMapPack *)mapPackNewestAvailableWithDirectory:(NSString *)directory;
{
    LocusLabsMapPackFinder *mapPackFinder = [LocusLabsMapPackFinder mapPackFinderWithDirectory:directory];
    return [LocusLabsMapPack mapPackNewestAvailableWithFinder:mapPackFinder];
}

+ (LocusLabsMapPack *)mapPackNewestAvailableWithFinder:(LocusLabsMapPackFinder *)finder
{
    return [LocusLabsMapPack mapPackWithPath:finder.newestMapPackPath];
}

+ (LocusLabsMapPack *)mapPackWithPath:(NSString *)path
{
    if (path) {
        return [[LocusLabsMapPack alloc] initWithPath:path];
    } else {
        return nil;
    }
}

+ (void)mapPackInstallWithCompletionBlock:(void (^)(BOOL didInstall, NSError *error))completionBlock
{
    LocusLabsMapPack *mapPack = [LocusLabsMapPack mapPackNewestAvailable];
    
    if (mapPack) {
        [mapPack installWithCompletionBlock:completionBlock];
    } else {
        completionBlock(FALSE,nil);
    }
}

- (id)initWithPath:(NSString *)path
{
    self = [super init];
    
    if (self) {
        _path = path;
        _cache = [LocusLabsCache defaultCache];
    }
    
    return self;
}

- (id)initWithPath:(NSString *)path cache:(LocusLabsCache *)cache
{
    self = [super init];
    
    if (self) {
        _path = path;
        _cache = cache;
    }
    
    return self;
}

- (NSString *)version
{
    NSRegularExpression *mapPackRegex = [NSRegularExpression regularExpressionWithPattern:[LocusLabsMapPackFinder mapPackFilenamePattern] options:0 error:nil];
    __block NSString *mapPackVersion;
    NSString *filename = [self.path lastPathComponent];
    
    [mapPackRegex enumerateMatchesInString:filename options:0 range:NSMakeRange(0, filename.length) usingBlock:^void(NSTextCheckingResult *result,NSMatchingFlags flags,BOOL *stop){
        mapPackVersion = [filename substringWithRange:[result rangeAtIndex:1]];
        *stop = YES;
    }];
    
    return mapPackVersion;
}

- (NSString *)installedVersion
{
    return [self.cache dateOnVenueList];
}

- (BOOL)needsInstall
{
    if (!self.installedVersion) {
        return true;
    }
    
    return [self.installedVersion compare:self.version] == NSOrderedAscending;
}

- (void)installWithCompletionBlock:(void (^)(BOOL didInstall, NSError *error))completionBlock
{
    if (!self.needsInstall) {
        completionBlock(false,nil);
        return;
    }

    LLLogDebug(@"starting install");
    [[NVHTarGzip sharedInstance] unTarGzipFileAtPath:self.path toPath:self.cache.cachePath completion:^(NSError* error) {
        if (error != nil) {
            completionBlock(false,error);
        } else {
            completionBlock(true,nil);
        }
    }];

}

@end
