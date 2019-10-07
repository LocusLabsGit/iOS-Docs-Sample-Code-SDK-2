//
//  LLMapPack.h
//  LocusLabsSDK
//
//  Created by Rafal Hotlos on 16/09/2019.
//  Copyright © 2019 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LLMapPackFinder;
@class LLCache;


/**
 * It is possible to bundle a map with your app to ensure that it will be available should the user not be connected
 * to the internet the first time he wants to use the map.
 * This class gives a programmatic access to map packs bundled with the app.
 */
@interface LLMapPack : NSObject

/**
 * Get the newest map pack from the app bundle
 */
+ (LLMapPack *)mapPackNewestAvailable;

/**
 * Get the newest map pack from given directory
 */
+ (LLMapPack *)mapPackNewestAvailableWithDirectory:(NSString *)directory;

/**
 * Get the newest map pack using given LLMapPackFinder
 */
+ (LLMapPack *)mapPackNewestAvailableWithFinder:(LLMapPackFinder *)finder;

/**
 * Load the map pack from given path
 */
+ (LLMapPack *)mapPackWithPath:(NSString *)path;

/**
 * Install the newest map pack from the app bundle
 */
+ (void)mapPackInstallWithCompletionBlock:(void (^)(BOOL didInstall, NSError *error))completionBlock;

/**
 * Init map pack with given path
 */
- (id)initWithPath:(NSString *)path;

/**
 * Map pack path in the file system.
 */
@property (strong, nonatomic, readonly) NSString *path;

/**
 * This map pack version
 */
- (NSString *)version;

/**
 * The version of the map pack currently installed in the app
 */
- (NSString *)installedVersion;

/**
 * Returns <code>YES</code> if there's no map pack installed, or it's older that this map pack
 */
- (BOOL)needsInstall;

/**
 * Install this map pack
 */
- (void)installWithCompletionBlock:(void (^)(BOOL didInstall, NSError *error))completionBlock;

@end

