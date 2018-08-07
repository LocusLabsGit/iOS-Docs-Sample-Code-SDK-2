//
//  ViewController.swift
//  DirectionsDrawSwift
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

import UIKit

class ViewController: UIViewController, LLVenueDatabaseDelegate, LLMapViewDelegate, LLVenueDelegate {

    // Vars
    var venueDatabase:      LLVenueDatabase!
    var venue:              LLVenue?
    var mapView:            LLMapView?
    
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
        
        
        // Get an instance of LLVenueDatabase, register as its delegate and load the venue LAX
        venueDatabase = LLVenueDatabase()
        venueDatabase.delegate = self
        
        // Load the venue LAX async
        venueDatabase.loadVenueAndMap("lax") { (_venue: LLVenue?, _map: LLMap?, _floor: LLFloor?, _marker: LLMarker?) in
            
            self.mapView?.map = _map
            self.venue = _venue
        }
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
        
        let point1 = LLPosition(floorId: mapView?.map.floorId, latLng: point1LatLon)
        let point2 = LLPosition(floorId: mapView?.map.floorId, latLng: point2LatLon)
        
        venue?.delegate = self
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
    
    // MARK: Delegates - LLMapView
    func mapViewDidClickBack(_ mapView: LLMapView!) {
        
        // The user tapped the "Cancel" button while the map was loading. Dismiss the app or take other appropriate action here
    }
    
    func mapViewReady(_ mapView: LLMapView!) {
        
        // Pan & zoom the map after selecting lax-south-departures
        mapView.levelSelected("lax-south-departures")
        mapView.mapCenter = LLLatLng(lat: 33.941384, lng: -118.402057)
        mapView.mapRadius = 190.0
        
        showSampleRoute()
    }
}

