//
//  ViewController.swift
//  DirectionsDrawSwift
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

import UIKit

class ViewController: UIViewController, LLVenueDatabaseDelegate, LLFloorDelegate, LLMapViewDelegate, LLVenueDelegate {

    // Vars
    var venueDatabase:      LLVenueDatabase!
    var venue:              LLVenue?
    var floor:              LLFloor?
    var mapView:            LLMapView?
    
    // MARK: Lifecycle
    
    override func viewDidLoad() {
        
        super.viewDidLoad()
        
        // Initialize the LocusLabs SDK with the accountId provided by LocusLabs
        LLLocusLabs.setup().accountId = "A11F4Y6SZRXH4X"
        
        // Get an instance of the LLVenueDatabase and register as its delegate
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
    func createCircleWith(position: LLPosition!, radius: NSNumber, color: UIColor!) {
        
        let circle = LLCircle();
        circle.fillColor = color
        circle.radius = radius
        circle.position = position
        circle.map = mapView?.map
    }
    
    func drawRoute(waypoints: [LLWaypoint], startFloor: String!) {
        
        let path = LLPath()
        for waypoint in waypoints {
            
            // Add this latLng to the LLPath
            path.add(waypoint.latLng)
            
            // Add a black circle at the destination
            if waypoint.isDestination == true {
                
                let position = LLPosition(floorId: startFloor, latLng: waypoint.latLng)
                createCircleWith(position: position, radius: 5, color: UIColor.black)
            }
        }
        
        // Create a new LLPolyline object and set its path
        let polyLine = LLPolyline()
        polyLine.path = path
        polyLine.floorId = startFloor
        polyLine.map = mapView?.map
    }
    
    func showSampleRoute() {
        
        let point1LatLon = LLLatLng(lat: 33.940627, lng: -118.401892)
        let point2LatLon = LLLatLng(lat: 33.9410700, lng: -118.399598)
        
        let point1 = LLPosition(floorId: floor?.identifier, latLng: point1LatLon)
        let point2 = LLPosition(floorId: floor?.identifier, latLng: point2LatLon)
        
        venue?.navigate(from: point1, to: point2)
    }

    // MARK: Delegates - LLVenue
    
    func venue(_ venue: LLVenue!, navigationPath: LLNavigationPath!, from startPosition: LLPosition!, toDestinations destinations: [Any]!) {
        
        drawRoute(waypoints: navigationPath.waypoints as! [LLWaypoint], startFloor: startPosition.floorId)
    }
    
    // MARK: Delegates - LLVenueDatabase
    
    func venueDatabase(_ venueDatabase: LLVenueDatabase!, venueLoadFailed venueId: String!, code errorCode: LLDownloaderError, message: String!) {
        
        // Handle failures here
    }
    
    // Implement the airportLoaded delegate method
    func venueDatabase(_ venueDatabase: LLVenueDatabase!, venueLoaded venue: LLVenue!) {
        
        self.venue = venue
        self.venue?.delegate = self
        
        let building = self.venue?.loadBuilding("lax-south")
        floor = building?.loadFloor("lax-south-departures")
        
        // Set the floor delegate and load its map - mapLoaded is called when loading is complete
        floor?.delegate = self
        floor?.loadMap()
    }

    // MARK: Delegates - LLFloor
    
    func floor(_ floor: LLFloor!, mapLoaded map: LLMap!) {
        
        mapView!.map = map
    }
    
    // MARK: Delegates - LLMapView
    
    func mapViewDidClickBack(_ mapView: LLMapView!) {
        
        // The user tapped the "Cancel" button while the map was loading. Dismiss the app or take other appropriate action here
    }
    
    func mapViewReady(_ mapView: LLMapView!) {
        
        // Pan/zoom the map after selecting lax-south-Departured
        mapView.levelSelected("lax-south-departures")
        mapView.mapCenter = LLLatLng(lat: 33.941384, lng: -118.402057)
        mapView.mapRadius = 190.0
        
        showSampleRoute()
    }
}

