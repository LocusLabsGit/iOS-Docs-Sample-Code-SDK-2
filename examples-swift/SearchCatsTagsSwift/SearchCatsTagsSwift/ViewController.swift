//
//  ViewController.swift
//  SearchGeneralSwift
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

import UIKit

class ViewController: UIViewController, LLVenueDatabaseDelegate, LLMapViewDelegate, LLSearchDelegate {

    // Vars
    var venueDatabase:      LLVenueDatabase!
    var venue:              LLVenue?
    var floor:              LLFloor?
    var mapView:            LLMapView?
    var search:             LLSearch?
    
    // MARK: Lifecycle
    override func viewDidLoad() {
        
        super.viewDidLoad()
        
        // Initialize the LocusLabs SDK with the accountId provided by LocusLabs
        LLLocusLabs.setup().accountId = "A11F4Y6SZRXH4X"
        
        // Create a new LLMapView, register as its delegate and add it as a subview
        mapView = LLMapView(frame: view.bounds)
        mapView?.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        mapView?.delegate = self
        view.addSubview(mapView!)
        
        // Get an instance of the LLVenueDatabase, register as its delegate and load the venue LAX
        venueDatabase = LLVenueDatabase()
        venueDatabase.delegate = self
        
        // Load the venue LAX async
        venueDatabase.loadVenueAndMap("lax") { (_venue: LLVenue?, _map: LLMap?, _floor: LLFloor?, _marker: LLMarker?) in
            
            self.mapView?.map = _map
            self.venue = _venue
            
            // Get a search instance and register as its delegate
            self.search = self.venue!.search()
            self.search?.delegate = self;
        }
    }

    // MARK: Custom
    
    func createCircle(position: LLPosition, radius: Float, color: UIColor) {
        
        let circle = LLCircle()
        circle.position = position
        circle.fillColor = color
        circle.radius = radius as NSNumber
        circle.map = mapView?.map
    }
    
    // MARK: Delegates - LLVenueDatabase
    
    func venueDatabase(_ venueDatabase: LLVenueDatabase!, venueLoadFailed venueId: String!, code errorCode: LLDownloaderError, message: String!) {
        
        // Handle failures here
    }

    // MARK: Delegates - LLMapView
    
    func mapViewDidClickBack(_ mapView: LLMapView!) {
        
        // The user tapped the "Cancel" button while the map was loading. Dismiss the app or take other appropriate action here
    }
    
    func mapViewReady(_ mapView: LLMapView!) {
        
        // Seach for all POIs in the "eat" category
        search?.search("category:eat")
        
        // Search for all POIs tagged "chocolate"
        search?.search("chocolate")
    }
    
    // MARK: Delegates - LLSearch
    
    func search(_ search: LLSearch!, results searchResults: LLSearchResults!) {
        
        let searchTerm = searchResults.query
        
        // For the category search, log available info
        if searchTerm == "category:eat" {
            
            for searchResult in searchResults.results as! [LLSearchResult] {
                
                // Each result contains general information about the poi in addition to its location
                print("Name: "+searchResult.name+" POIID: "+searchResult.poiId)
                print("Terminal: "+searchResult.terminal+" Gate: "+searchResult.gate)
            }
        }
        // For the tag search, draw results on the map
        else if searchTerm == "chocolate" {
            
            for searchResult in searchResults.results as! [LLSearchResult] {
                
                let position = searchResult.position
                createCircle(position: position!, radius: 8, color: UIColor.brown)
            }
        }
    }
}
