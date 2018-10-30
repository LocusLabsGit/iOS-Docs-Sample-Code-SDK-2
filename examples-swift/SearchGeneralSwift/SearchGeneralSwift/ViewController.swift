//
//  ViewController.swift
//  SearchGeneralSwift
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

import UIKit

class ViewController: UIViewController, LLVenueDatabaseDelegate, LLMapViewDelegate, LLPOIDatabaseDelegate, LLSearchDelegate {

    // Vars
    var venueDatabase:      LLVenueDatabase!
    var venue:             LLVenue?
    var floor:              LLFloor?
    var mapView:            LLMapView?
    var poiDatabase:        LLPOIDatabase?
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
            
            // Get an instance of the POI Database and register as its delegate
            self.poiDatabase = self.venue!.poiDatabase()
            self.poiDatabase?.delegate = self
            
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
        
        search?.search("gate 62")
        search?.search("Food")
    }
    
    // MARK: Delegates - LLPOIDatabase
    
    func poiDatabase(_ poiDatabase: LLPOIDatabase!, poiLoaded poi: LLPOI!) {
        
        // We only want to mark "Food" results on the map that fall in the "Eat" category
        if poi.category == "eat" {
            
            let position = poi.position
            createCircle(position: position!, radius: 10, color: UIColor.blue)
        }
    }
    
    // MARK: Delegates - LLSearch
    
    func search(_ search: LLSearch!, results searchResults: LLSearchResults!) {
        
        let searchTerm = searchResults.query
        
        // For the "gate 62" search, place a dot on the map immediately
        if searchTerm == "gate 62" {
            
            for searchResult in searchResults.results as! [LLSearchResult] {
                
                let position = searchResult.position
                createCircle(position: position!, radius: 10, color: UIColor.yellow)
            }
        }
        // For the "Restaurant" search, get more information for each result from the poiDatabase before displaying
        else if searchTerm == "Food" {
            
            for searchResult in searchResults.results as! [LLSearchResult] {
                
                poiDatabase?.loadPOI(searchResult.poiId)
            }
        }
    }
}

