//
//  LocusLabsCache.m
//  RecommendedImplementation
//
//  Created by Sam Ziegler on 7/12/15.
//  Copyright (c) 2015 LocusLabs. All rights reserved.
//

#import "LocusLabsCache.h"

#import "LocusLabsSDK/LocusLabsSDK.h"

@implementation LocusLabsCache

+ (LocusLabsCache *)defaultCache
{
    NSString *cacheDirectory = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    NSString *locusLabsCache = [cacheDirectory stringByAppendingPathComponent:@"locuslabs"];
    
    return [[LocusLabsCache alloc] initWithCachePath:locusLabsCache];
}

+ (NSString *)filenameForAsset:(NSString *)asset {
    return [asset stringByReplacingOccurrencesOfString:@"/" withString:@"-"];
}

- (id)initWithCachePath:(NSString *)cachePath
{
    self = [super init];
    
    if (self) {
        _cachePath = cachePath;
    }
    
    return self;
}

- (NSString *)pathForAssset:(NSString *)asset
{
    return [self.cachePath stringByAppendingPathComponent:[LocusLabsCache filenameForAsset:asset]];
}

- (NSString *)venueListAsset
{
    return [NSString stringWithFormat:@"accounts/%@/%@.js",[LLLocusLabs setup].accountId, [LLLocusLabs setup].assetsFormatVersion];
}

- (NSString*)dateOnVenueList
{
    NSURL *fileUrl = [NSURL fileURLWithPath:[self pathForAssset:[self venueListAsset]]];
    NSDate *fileDate;
    NSError *error;
    [fileUrl getResourceValue:&fileDate forKey:NSURLContentModificationDateKey error:&error];
    if (error) {
        return nil;
    }
    else {
        NSDateFormatter* df = [[NSDateFormatter alloc] init];
        [df setDateFormat:@"yyyy-MM-dd'T'HH:mm:ss"];
        
        return [df stringFromDate:fileDate];
    }
}

- (BOOL)setup
{
    NSError *err;
    [[NSFileManager defaultManager] createDirectoryAtPath:self.cachePath withIntermediateDirectories:YES attributes:0 error:&err];
    return err == nil;
}

- (BOOL)tearDown
{
    NSError *err;
    [[NSFileManager defaultManager] removeItemAtPath:self.cachePath error:&err];
    
    return err == nil;
}

- (void)clear
{
    [self tearDown];
    [self setup];
}

- (BOOL)isValid
{
    BOOL isDirectory;
    if (![[NSFileManager defaultManager] fileExistsAtPath:self.cachePath isDirectory:&isDirectory]) {
        return false;
    }
    
    return isDirectory;
}

- (BOOL)isEmpty
{
    if (!self.isValid) {
        return true;
    }
    
    NSArray *contents = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:self.cachePath error:nil];
    
    return contents.count == 0;
}

@end
