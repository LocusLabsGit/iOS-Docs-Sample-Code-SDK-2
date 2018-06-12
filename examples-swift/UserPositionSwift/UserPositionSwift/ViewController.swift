//
//  ViewController.swift
//  ShowFullScreenMapSwift
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

import UIKit

class ViewController: UIViewController, LLVenueDatabaseDelegate, LLFloorDelegate, LLMapViewDelegate, LLPositionManagerDelegate {

    // Vars
    var venueDatabase:      LLVenueDatabase!
    var venue:              LLVenue?
    var floor:              LLFloor?
    var mapView:            LLMapView?
    var positionManager:    LLPositionManager?
    
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
    
    func startTrackingUserPosition() {
        
        positionManager = LLPositionManager(venues: [venue as Any])
        positionManager?.delegate = self
        
        // Start with passive positioning to conserve battery
        positionManager?.passivePositioning = true;
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
        startTrackingUserPosition()
    }
    
    // MARK: Delegates - LLMapView
    
    func mapViewDidClickBack(_ mapView: LLMapView!) {
        
        // The user tapped the "Cancel" button while the map was loading. Dismiss the app or take other appropriate action here
    }
    
    func mapViewReady(_ mapView: LLMapView!) {
        
        // The map is ready to be used in calls e.g. zooming, showing poi, etc.
    }
    
    // MARK: Delegates LL PositionManager
    func positionManager(_ positionManager: LLPositionManager!, positioningAvailable: Bool) {
        
        if positioningAvailable {
            
            print("Positioning available")
        }
        else {
            
            print("Positioning not available - determine if bluetooth is active and prompt user if not.")
        }
    }
    
    func positionManager(_ positionManager: LLPositionManager!, positionChanged position: LLPosition!) {
        
        if position == nil {
            
            print("Unable to locate user")
            return
        }
        
        // If we're near a venue, start active positioning (more battery intensive but provides accurate tracking)
        if position.venueId != nil {
            
            positionManager.activePositioning = true
            print("Near venueId: %@", position.venueId)
        }
    }
}

