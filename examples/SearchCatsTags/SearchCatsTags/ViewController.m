//
//  ViewController.m
//  SearchGeneral
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property (nonatomic, strong) LLVenue           *venue;
@property (nonatomic, strong) LLVenueDatabase   *venueDatabase;
@property (nonatomic, weak)   LLMapView         *mapView;
@property (nonatomic, strong) LLSearch          *search;

- (void)createCircleWithPosition:(LLPosition *)position withRadius:(NSNumber*)radius andColor:(UIColor*)color;

@end

@implementation ViewController

#pragma mark Lifecycle

- (void)viewDidLoad {
    
    // Initialize the LocusLabs SDK with the accountId provided by LocusLabs
    [LLLocusLabs setup].accountId = @"A11F4Y6SZRXH4X";
    
    // Create a new LLMapView, register as its delegate and add it as a subview
    LLMapView *mapView = [[LLMapView alloc] initWithFrame:self.view.bounds];
    mapView.autoresizingMask = (UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight);
    mapView.delegate = self;
    [self.view addSubview:mapView];
    
    self.mapView = mapView;
    
    // Get an instance of the LLAirportDatabase, set it's mapview and register as its delegate
    self.venueDatabase = [LLVenueDatabase venueDatabaseWithMapView:self.mapView];
    self.venueDatabase.delegate = self;
    
    // Load the venue LAX async
    [self.venueDatabase loadVenueAndMap:@"lax" block:^(LLVenue *venue, LLMap *map, LLFloor *floor, LLMarker *marker) {
        
        self.mapView.map = map;
        self.venue = venue;
        
        // Get a search instance and register as its delegate
        self.search = [self.venue search];
        self.search.delegate = self;
    }];
}

#pragma mark Custom

- (void)createCircleWithPosition:(LLPosition *)position withRadius:(NSNumber*)radius andColor:(UIColor*)color {
    
    LLCircle *circle = [LLCircle new];
    circle.fillColor = color;
    circle.radius = radius;
    circle.position = position;
    circle.map = self.mapView.map;
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
    
    // Seach for all POIs in the "eat" category
    [self.search search:@"category:eat"];
    
    // Search for all POIs tagged "chocolate"
    [self.search search:@"chocolate"];
}

#pragma mark Delegates - LLSearch

- (void)search:(LLSearch *)search results:(LLSearchResults *)searchResults {
    
    NSString *searchTerm = searchResults.query;
    
    // For the category search, log available info
    if ([searchTerm isEqualToString:@"category:eat"]) {
    
        for (LLSearchResult *searchResult in searchResults.results) {
            
            // Each result contains general information about the poi in addition to its location
            NSLog(@"%@ %@ %@ %@", searchResult.name, searchResult.poiId, searchResult.terminal, searchResult.gate);
        }
    }
    // For the tag search, draw results on the map
    else if ([searchTerm isEqualToString:@"chocolate"]) {
    
        for (LLSearchResult *searchResult in searchResults.results) {
            
            // Mark all chocolate results on the map
            LLPosition *position = searchResult.position;
            [self createCircleWithPosition:position withRadius:@8 andColor:[UIColor brownColor]];
        }
    }
}

@end
