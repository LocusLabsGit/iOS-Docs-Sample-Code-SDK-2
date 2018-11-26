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
- (void)performANDSearch;
- (void)performORSearch;

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

- (void)performANDSearch {

    [self.search multiTermSearch:@[@"Beer", @"Burger"]];
}

- (void)performORSearch {
    
    [self.search searchWithTerms:@[@"Beer", @"Burger"]];
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
    
    // Perform a search for all POIs that match either Beer OR Burger
    [self performORSearch];
    
    // Perform a search for all POIs that match Beer AND Burger
    //[self performANDSearch];
}

#pragma mark Delegates - LLSearch

- (void)search:(LLSearch *)search multiTermSearchResults:(LLMultiTermSearchResults *)searchResults {
    
    //print("count",searchResults.results.count)
    for (LLSearchResult *searchResult in searchResults.results) {
        
        [self createCircleWithPosition:searchResult.position withRadius:@10 andColor:[UIColor blueColor]];
    }
}

- (void)searchWithTerms:(LLSearch *)search results:(LLSearchResults *)searchResults {
    //print("count",searchResults.results.count)
    for (LLSearchResult *searchResult in searchResults.results) {
        
        [self createCircleWithPosition:searchResult.position withRadius:@10 andColor:[UIColor blueColor]];
    }
}

@end
