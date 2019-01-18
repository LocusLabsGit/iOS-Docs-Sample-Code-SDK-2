//
//  ViewController.swift
//  SearchTermsSwift
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
        venueDatabase = LLVenueDatabase(mapView: mapView)
        venueDatabase.delegate = self
        
        // Load the venue LAX async
        venueDatabase.loadVenueAndMap("lax") { (_venue: LLVenue?, _map: LLMap?, _floor: LLFloor?, _marker: LLMarker?) in
            
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
    
    func performANDSearch() {
        
        search?.multiTermSearch(["Beer","Burger"])
    }
    
    func performORSearch() {
        
        search?.search(withTerms: ["Beer","Burger"])
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
        
        // Perform a search for all POIs that match either Beer OR Burger
        performORSearch()
        
        // Perform a search for all POIs that match Beer AND Burger
        //performANDSearch()
    }
    
    // MARK: Delegates - LLSearch
    func search(_ search: LLSearch!, multiTermSearchResults searchResults: LLMultiTermSearchResults!) {
        
        for searchResult in searchResults.results as! [LLSearchResult] {
            
            let position = searchResult.position
            createCircle(position: position!, radius: 10, color: UIColor.blue)
        }
    }
    
    func search(withTerms search: LLSearch!, results searchResults: LLSearchResults!) {
        
        for searchResult in searchResults.results as! [LLSearchResult] {
        
            let position = searchResult.position
            createCircle(position: position!, radius: 10, color: UIColor.blue)
        }
    }
}

