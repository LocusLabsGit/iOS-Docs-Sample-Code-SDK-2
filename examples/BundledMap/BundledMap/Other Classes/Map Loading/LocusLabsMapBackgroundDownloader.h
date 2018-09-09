//
//  LocusLabsMapDownloader.h
//  RecommendedImplementation
//
//  Created by Sam Ziegler on 7/12/15.
//  Copyright (c) 2015 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LocusLabsCache;

@interface LocusLabsMapBackgroundDownloader : NSObject

@property (strong,nonatomic,readonly) NSString *venueId;

+ (LocusLabsMapBackgroundDownloader *)mapBackgroundDownloaderWithVenueId:(NSString *)venueId;

- (id)initWithVenueId:(NSString *)venueId;

- (void)downloadWithCompletionBlock:(void (^)(BOOL didDownload, NSError *err))completionBlock;

@end
