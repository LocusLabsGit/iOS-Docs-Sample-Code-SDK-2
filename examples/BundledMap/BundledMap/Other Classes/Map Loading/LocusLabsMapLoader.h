//
//  LocusLabMapLoader.h
//  RecommendedImplementation
//
//  Copyright (c) 2015 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <LocusLabsSDK/LocusLabsSDK.h>

@class LocusLabsMapLoader;

@protocol LocusLabMapLoaderDelegate <NSObject>

@required
- (void)mapLoaderReady:(LocusLabsMapLoader*)loader;
- (void)mapLoaderClosed:(LocusLabsMapLoader*)loader;

@optional
- (void)mapLoaderInitialized:(LocusLabsMapLoader*)loader;
- (NSString*)departingGateForMapLoader:(LocusLabsMapLoader*)loader;
- (void)mapLoaderFinishedDownload:(LocusLabsMapLoader*)loader;
- (void)mapLoader:(LocusLabsMapLoader*)loader isLoadingWithProgress:(float)progress;
- (void)mapLoader:(LocusLabsMapLoader*)loader failedWithError:(NSError*)error;

@end

@interface LocusLabsMapLoader : NSObject

- (instancetype)initWithSuperview:(UIView*)superview;
- (void)loadMap:(NSString*)venueId showGate:(NSString*)gate;
- (void)resetMap;

@property (nonatomic, weak) id<LocusLabMapLoaderDelegate> delegate;
@property (nonatomic, readonly) LLMapView *mapView;

@end