//
//  ViewController.swift
//  ShowFullScreenMapSwift
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

import UIKit

class ViewController: UIViewController, LLVenueDatabaseDelegate, LLFloorDelegate, LLMapViewDelegate, LLPOIDatabaseDelegate {

    // Vars
    var venueDatabase:      LLVenueDatabase!
    var venue:              LLVenue?
    var floor:              LLFloor?
    var mapView:            LLMapView?
    var poiDatabase:        LLPOIDatabase?
    var customMarkers:      Array<LLMarker>?
    
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

    // MARK: Delegates - LLVenueDatabase
   
    func venueDatabase(_ venueDatabase: LLVenueDatabase!, venueLoadFailed venueId: String!, code errorCode: LLDownloaderError, message: String!) {
        
        // Handle failures here
    }
    
    func venueDatabase(_ venueDatabase: LLVenueDatabase!, venueLoaded venue: LLVenue!) {
        
        self.venue = venue
        
        /// Get a list of buildings in this airport and load the first one
        if let buildingInfo = self.venue?.listBuildings().first as? LLBuildingInfo {
            
            let building = self.venue?.loadBuilding(buildingInfo.buildingId)
            
            // Get a list of floors for the building and load the first one
            if let floorInfo = building?.listFloors().first as? LLFloorInfo {
                
                floor = building?.loadFloor(floorInfo.floorId)
                
                // Set the floor delegate and load its map - mapLoaded is called when loading is complete
                floor?.delegate = self
                floor?.loadMap()
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
        
        // Get a reference to the POI database and set its delegate
        poiDatabase = venue?.poiDatabase()
        poiDatabase?.delegate = self
        
        // Load the POI for Starbucks at gate 60 (to find out a POI's id, implement mapView's didTapPOI delegate method)
        poiDatabase?.loadPOI("870")
    }
    
    // MARK: Delegates - LLPOIDatabase
    func poiDatabase(_ poiDatabase: LLPOIDatabase!, poiLoaded poi: LLPOI!) {
        
        if poi.poiId == "870" {
         
            // Add a custom marker
            let marker = LLMarker()
            marker.position = poi.position
            marker.iconUrl = Bundle.main.path(forResource: "starbucks_selected.svg", ofType: nil)
            marker.userData = poi
            marker.map = mapView?.map
            
            // Keep a reference to the marker so you can remove it when necessary
            if customMarkers == nil {customMarkers = [LLMarker]()}
            customMarkers?.append(marker)
        }
    }
}

