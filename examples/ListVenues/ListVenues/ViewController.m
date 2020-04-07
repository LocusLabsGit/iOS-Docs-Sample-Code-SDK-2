//
//  ViewController.m
//  ShowFullscreenMap
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

#import "ViewController.h"
#import "MapController.h"

@interface ViewController ()

@property (nonatomic, strong) NSArray           *venues;
@property (nonatomic, strong) LLVenueDatabase   *venueDatabase;

@end

@implementation ViewController {
    
}

#pragma mark Lifecycle

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    self.title = @"Venues";
    
    // Initialize the LocusLabs SDK with the accountId provided by LocusLabs
    [LLLocusLabs setup].accountId = @"A11F4Y6SZRXH4X";
    
    // Load the venue database
    self.venueDatabase = [LLVenueDatabase venueDatabase];
    self.venueDatabase.delegate = self;
    
    [self.venueDatabase listVenues];
}

#pragma mark Delegates - LLVenueDatabase

- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueLoadFailed:(NSString *)venueId code:(LLDownloaderError)errorCode message:(NSString *)message {

    // Handle failures here
}

- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueList:(NSArray *)venueList {
    
    self.venues = [venueList sortedArrayUsingDescriptors:@[[NSSortDescriptor sortDescriptorWithKey:@"name" ascending:YES]]];
    [self.tableView reloadData];
}

#pragma mark Delegates - TableView

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    
    return [self.venues count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {

    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];

    if (!cell) {
        
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    
    LLVenueInfo *venueInfo = self.venues[indexPath.row];
    cell.textLabel.text = [NSString stringWithFormat:@"%@ (%@)", venueInfo.name, [venueInfo.airportCode uppercaseString]];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    LLVenueInfo *venueInfo = self.venues[indexPath.row];
    
    MapController *mapController = [[MapController alloc] init];
    mapController.venueID = venueInfo.venueId;
    [self.navigationController pushViewController:mapController animated:YES];
}

@end
