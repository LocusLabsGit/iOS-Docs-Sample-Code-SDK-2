//
//  ViewController.swift
//  ShowFullScreenMapSwift
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

import UIKit

class ViewController: UIViewController, LLVenueDatabaseDelegate, LLFloorDelegate, LLPositionManagerDelegate, LLMapViewDelegate {

    // Vars
    var venueDatabase:      LLVenueDatabase!
    var venue:              LLVenue?
    var floor:              LLFloor?
    var mapView:            LLMapView?
    var navPoint:           LLNavPoint?
    var positionManager:    LLPositionManager?
    
    var initialZoomDone =   false;
    
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
    
    func locationDict(lat: NSNumber!, lon:NSNumber!) -> [String: Any]  {
    
        let latLng = LLLatLng(lat: lat, lng: lon)
        
        var locationDict = [String: Any]()
        locationDict["latLng"] = latLng
        locationDict["errorRadius"] = NSNumber(value: 1)
        locationDict["floorId"] = "lax-south-departures"
        locationDict["heading"] = NSNumber(value: 34)
        
        return locationDict
    }
    
    func postUserPosition(locationDict: [String: Any]!) {
        
        NotificationCenter.default.post(name: NSNotification.Name(rawValue: NOTIFICATION_POSITION_SENSOR_POSITION_CHANGED), object: nil, userInfo: locationDict)
    }
    
    func startTrackingUserPosition() {
        
        positionManager = LLPositionManager(airports: [airport as Any])
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
        mapView?.positioningEnabled = true
    }
    
    // MARK: Delegates - LLMapView
    func mapViewReady(_ mapView: LLMapView!) {
        
        // Set the navigation source to internal & send timed navigation points
        let algorithm = NSNumber(value: Int8(LLPositioningSensorAlgorithmExternal.rawValue))
        NotificationCenter.default.post(name: NSNotification.Name(rawValue: NOTIFICATION_SET_POSITIONING_SENSOR_ALGORITHM), object: nil, userInfo: ["positioningSensorAlgorithm": algorithm])
        
        // Position 1 (Initial - DFS Duty Free)
        var locationDict = self.locationDict(lat: NSNumber(value: 33.941485), lon: NSNumber(value: -118.40195))
        postUserPosition(locationDict: locationDict)
        
        // Position 2 (2 secs later)
        DispatchQueue.main.asyncAfter(deadline: .now() + .seconds(2)) {
           
            locationDict = self.locationDict(lat: NSNumber(value: 33.941398), lon: NSNumber(value: -118.401916))
            self.postUserPosition(locationDict: locationDict)
        }
        
        // Position 3 (4 secs later)
        DispatchQueue.main.asyncAfter(deadline: .now() + .seconds(4)) {
            
            locationDict = self.locationDict(lat: NSNumber(value: 33.941283), lon: NSNumber(value: -118.401863))
            self.postUserPosition(locationDict: locationDict)
        }
        
        // Position 4 (6 secs later)
        DispatchQueue.main.asyncAfter(deadline: .now() + .seconds(6)) {
            
            locationDict = self.locationDict(lat: NSNumber(value: 33.941102), lon: NSNumber(value: -118.401902))
            self.postUserPosition(locationDict: locationDict)
        }
        
        // Position 5 (8 secs later - Destination - Gate 64B)
        DispatchQueue.main.asyncAfter(deadline: .now() + .seconds(8)) {
            
            locationDict = self.locationDict(lat: NSNumber(value: 33.940908), lon: NSNumber(value: -118.40177))
            self.postUserPosition(locationDict: locationDict)
        }
    }
    
    // MARK: Delegates - LLPositionManager
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
        
        // For the first simulated location, zoom in on the user's position
        if !initialZoomDone {
            
            mapView?.mapCenter = LLLatLng(lat: position.latLng.lat, lng: position.latLng.lng)
            mapView?.mapRadius = NSNumber(value: 50.0)
            initialZoomDone = true;
        }
        
        // If we're near a venue, start active positioning (more battery intensive but provides accurate tracking)
        if position.venueId != nil {
            
            positionManager.activePositioning = true
            print("Near venueId: %@", position.venueId)
        }
    }
}

