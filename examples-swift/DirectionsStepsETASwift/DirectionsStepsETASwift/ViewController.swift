//
//  ViewController.swift
//  ShowFullScreenMapSwift
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

import UIKit

class ViewController: UIViewController, LLVenueDatabaseDelegate, LLMapViewDelegate {

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
        mapView?.showTopSafeAreaOverlay = false
        view.addSubview(mapView!)
        
        // Get an instance of LLVenueDatabase, register as its delegate and load the venue LAX
        venueDatabase = LLVenueDatabase(mapView: mapView)
        venueDatabase.delegate = self
        
        // Load the venue LAX async
        venueDatabase.loadVenueAndMap("lax") { (_venue: LLVenue?, _map: LLMap?, _floor: LLFloor?, _marker: LLMarker?) in
            
            self.venue = _venue
        }
    }
    
    // MARK: Custom
    func getDirectionsAndETA() {
        
        // From: Blu20 Bar, Level 3, Terminal 6, ID 1025
        // To: Gate 73, Level 3, Terminal 7, ID 551
        // Note: if you dont have poi data to get a position from, you can also construct a LLPosition directly using this method: "LLPosition *positionStart = [[LLPosition alloc] initWithFloorId: latLng:];
        venue?.poiDatabase()?.loadPois(["1025", "551"], with: { pois in
        
            var startPOI: LLPOI? = nil
            var endPOI: LLPOI? = nil
            for poi in pois as! [LLPOI] {
                
                if poi.poiId == "1025" {startPOI = poi}
                else if poi.poiId == "551" {endPOI = poi}
            }
            
            if startPOI == nil || endPOI == nil {return}
            
            let directionsRequest = LLDirectionsRequest(start: startPOI!.position!, end: endPOI!.position!)
            
            self.venue?.navigate(directionsRequest, completion: { (navigationPath, error) in
                
                print("ETA:", navigationPath?.eta ?? 0)
                for wayPoint in navigationPath?.waypoints as! [LLWaypoint] {
                    
                    print("Waypoint:");
                    print("ETA:%@", wayPoint.eta ?? 0);
                    print("Distance:%@", wayPoint.distance ?? 0);
                    print("Details:%@", wayPoint.details ?? "");
                    print("Security Checkpoint?:%@", wayPoint.securityCheckpoint ?? false);
                    print("\n");
                }
            })
        })
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
        
        // The map is ready to be used in calls e.g. zooming, showing poi, etc.
        getDirectionsAndETA()
    }
    
    func presentingController(for mapView: LLMapView!, for context: LLMapViewPresentationContext) -> UIViewController! {
        
        return self
    }
}

