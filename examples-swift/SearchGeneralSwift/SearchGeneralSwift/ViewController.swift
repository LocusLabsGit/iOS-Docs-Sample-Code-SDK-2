//
//  ViewController.swift
//  SearchGeneralSwift
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

import UIKit

class ViewController: UIViewController, LLVenueDatabaseDelegate, LLFloorDelegate, LLMapViewDelegate, LLPOIDatabaseDelegate, LLSearchDelegate {

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
        
        // Get an instance of the LLVenueDatabase, register as its delegate and load the venue LAX
        venueDatabase = LLVenueDatabase()
        venueDatabase.delegate = self
        
        // Create a new LLMapView, register as its delegate and add it as a subview
        mapView = LLMapView()
        mapView!.delegate = self
        view.addSubview(mapView!)
        
        // Set the mapview's layout constraints
        mapView!.translatesAutoresizingMaskIntoConstraints = false
        mapView!.leftAnchor.constraint(equalTo: view.leftAnchor, constant: 0).isActive = true
        mapView!.rightAnchor.constraint(equalTo: view.rightAnchor, constant: 0).isActive = true
        mapView!.topAnchor.constraint(equalTo: view.topAnchor, constant: 0).isActive = true
        mapView!.bottomAnchor.constraint(equalTo: view.bottomAnchor, constant: 0).isActive = true
        
        venueDatabase.loadVenue("lax")
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
    
    func venueDatabase(_ venueDatabase: LLVenueDatabase!, venueLoaded venue: LLVenue!) {
        
        self.venue = venue
        
        // Get a list of buildings in this airport and load the first one
        if let buildingInfo = self.venue?.listBuildings().first as? LLBuildingInfo {
            
            let building = self.venue?.loadBuilding(buildingInfo.buildingId)
            
            // Get a list of floors for the building and load the first one
            if let floorInfo = building?.listFloors().first as? LLFloorInfo {
                
                floor = building?.loadFloor(floorInfo.floorId)
                
                // Set the floor delegate and load its map - mapLoaded is called when loading is complete
                floor?.delegate = self
                floor?.loadMap()
                
                // Get an instance of the POI Database and register as its delegate
                poiDatabase = venue.poiDatabase()
                poiDatabase?.delegate = self
                
                // Get a search instance and register as its delegate
                search = venue.search()
                search?.delegate = self;
            }
        }
    }

    // MARK: Delegates - LLFloor
    
    func floor(_ floor: LLFloor!, mapLoaded map: LLMap!) {
        
        mapView?.map = map
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

