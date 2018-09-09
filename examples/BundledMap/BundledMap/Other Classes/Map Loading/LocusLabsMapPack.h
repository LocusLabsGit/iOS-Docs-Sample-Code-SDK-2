//
//  LocusLabsMapPack.h
//  RecommendedImplementation
//
//  Created by Sam Ziegler on 7/12/15.
//  Copyright (c) 2015 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LocusLabsCache;
@class LocusLabsMapPackFinder;

@interface LocusLabsMapPack : NSObject

@property (strong,nonatomic,readonly) NSString *path;
@property (strong,nonatomic,readonly) LocusLabsCache *cache;

+ (LocusLabsMapPack *)mapPackNewestAvailable;
+ (LocusLabsMapPack *)mapPackNewestAvailableWithDirectory:(NSString *)directory;
+ (LocusLabsMapPack *)mapPackNewestAvailableWithFinder:(LocusLabsMapPackFinder *)finder;
+ (LocusLabsMapPack *)mapPackWithPath:(NSString *)path;
+ (void)mapPackInstallWithCompletionBlock:(void (^)(BOOL didInstall, NSError *error))completionBlock;

- (id)initWithPath:(NSString *)path;
- (id)initWithPath:(NSString *)path cache:(LocusLabsCache *)cache;

- (NSString *)version;
- (NSString *)installedVersion;
- (BOOL)needsInstall;
- (void)installWithCompletionBlock:(void (^)(BOOL didInstall, NSError *error))completionBlock;

@end
