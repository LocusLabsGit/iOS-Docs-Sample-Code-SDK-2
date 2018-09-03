//
//  ViewController.m
//  ShowFullscreenMap
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property (nonatomic, strong) LLVenue           *venue;
@property (nonatomic, strong) LLVenueDatabase   *venueDatabase;
@property (nonatomic, weak)   LLMapView         *mapView;

@end

@implementation ViewController

#pragma mark Lifecycle

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    // Initialize the LocusLabs SDK with the accountId provided by LocusLabs
    [LLLocusLabs setup].accountId = @"A11F4Y6SZRXH4X";
    
    // Create a new LLMapView, register as its delegate and add it as a subview
    LLMapView *mapView = [[LLMapView alloc] initWithFrame:self.view.bounds];
    mapView.autoresizingMask = (UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight);
    mapView.delegate = self;
    [self.view addSubview:mapView];
    
    self.mapView = mapView;
    
    // Get an instance of LLVenueDatabase, set it's mapview and register as its delegate
    self.venueDatabase = [LLVenueDatabase venueDatabaseWithMapView:self.mapView];
    self.venueDatabase.delegate = self;
    
    // Load the venue LAX async
    [self.venueDatabase loadVenueAndMap:@"lax" block:^(LLVenue *venue, LLMap *map, LLFloor *floor, LLMarker *marker) {
        
        self.mapView.map = map;
        self.venue = venue;
    }];
}

#pragma mark Delegates - LLVenueDatabase

- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueLoadFailed:(NSString *)venueId code:(LLDownloaderError)errorCode message:(NSString *)message {

    // Handle failures here
}

#pragma mark Delegates - LLMapView

- (void)mapViewDidClickBack:(LLMapView *)mapView {
    
    // The user tapped the "Cancel" button while the map was loading. Dismiss the app or take other appropriate action here
}

- (void)mapViewReady:(LLMapView *)mapView {
    
    // Show POI 870, which is the Starbucks near gate 60 at LAX - you can find POI IDs using our Venue Management System (VMS) or by imlpementing the "didTapPOI" delegate method
    [self.mapView showPoiByPoiId:@"870"];
}

- (NSArray *)mapView:(LLMapView *)mapView additionalViewsForPOI:(NSString *)poiId {
    
    NSMutableArray *additionalViews = [NSMutableArray array];
    
    // Only add extra buttons for the Starbucks POI
    if ([poiId isEqualToString:@"870"]) {
    
        LLIconButton *button1 = [LLIconButton topIconButtonWithPadding:0 image:[UIImage imageNamed:@"custom_icon_1.png"] andLabel:@"Custom1"];
        [additionalViews addObject:button1];
        
        [button1 addTarget:self action:@selector(customPoiButtonTapped) forControlEvents:UIControlEventTouchUpInside];
    }
    
    return additionalViews;
}

- (void)customPoiButtonTapped {
    
    NSLog(@"Custom POI Button tapped");
}

@end
