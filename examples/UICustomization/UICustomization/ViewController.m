//
//  ViewController.m
//  UICustomization
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property (nonatomic, strong) LLVenue           *venue;
@property (nonatomic, strong) LLVenueDatabase   *venueDatabase;
@property (nonatomic, weak)   LLMapView         *mapView;

- (LLTheme *)themeWithCustomBottomBar;
- (LLTheme *)themeWithCustomFont:(UIFont *)customFont;

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
        
        self.venue = venue;
    }];
}

#pragma mark Custom

- (LLTheme *)themeWithCustomBottomBar {
    
    LLThemeBuilder *themeBuilder = [LLThemeBuilder themeBuilderWithTheme:[LLTheme defaultTheme]];
    [themeBuilder setProperty:@"MapView.BottomBar.backgroundColor" value:[UIColor orangeColor]];
    [themeBuilder setProperty:@"MapView.BottomBar.Button.Title.textColor" value:[UIColor blackColor]];
    
    return themeBuilder.theme;
}

- (LLTheme *)themeWithCustomFont:(UIFont *)customFont {
    
    LLThemeBuilder *themeBuilder = [LLThemeBuilder themeBuilderWithTheme:[LLTheme defaultTheme]];
    [themeBuilder setProperty:@"fonts.normal" value:customFont];
    
    return themeBuilder.theme;
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
    
    // Set a custom font
    // self.mapView.theme = [self themeWithCustomFont:[UIFont fontWithName:@"American Typewriter" size:12.0]];
    
    // Set a custom back button title
    //self.mapView.backButtonText = NSLocalizedString(@"Back", nil);
    
    // Change the search bar background color
    //[self.mapView setSearchBarBackgroundColor:[UIColor orangeColor]];
    
    // Change the bottom bar background and button title colors
    //self.mapView.theme = [self themeWithCustomBottomBar];
    
    LLThemeBuilder *themeBuilder = [LLThemeBuilder themeBuilderWithTheme:[LLTheme defaultTheme]];
    [themeBuilder setProperty:@"MapView.TopBar.SearchBar.Text.textColor" value:[UIColor magentaColor]];
    self.mapView.theme = themeBuilder.theme;
}

@end
