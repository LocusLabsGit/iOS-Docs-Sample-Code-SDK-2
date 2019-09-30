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
        
        // Set accessibility preference for the user (this affects the preference toggle in the directions interface)
        LLUserPreferences.shared().preferWheelchairAccessibleNavigation = true
        
        // Create a new LLMapView, register as its delegate and add it as a subview
        mapView = LLMapView(frame: view.bounds)
        mapView?.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        mapView?.delegate = self
        view.addSubview(mapView!)
        
        // Get an instance of LLVenueDatabase, register as its delegate and load the venue LAX
        venueDatabase = LLVenueDatabase(mapView: mapView)
        venueDatabase.delegate = self
        
        // Load the venue LAX async
        venueDatabase.loadVenueAndMap("lax") { (_venue: LLVenue?, _map: LLMap?, _floor: LLFloor?, _marker: LLMarker?) in
            
            self.venue = _venue
            self.requestWheelchairDirectionsAndETAProgrammatically()
        }
    }
    
    func requestWheelchairDirectionsAndETAProgrammatically() {
        
        let point1LatLon = LLLatLng(lat: 33.940627, lng: -118.401892)
        let point2LatLon = LLLatLng(lat: 33.9410700, lng: -118.399598)
        
        let positionStart = LLPosition(floorId: "lax-south-departures", latLng: point1LatLon)
        let positionEnd = LLPosition(floorId: "lax-south-departures", latLng: point2LatLon)
        
        let directionsRequest = LLDirectionsRequest(start: positionStart!, end: positionEnd!)
        
        // Specify wheelchair accessible directions only
        directionsRequest.forceWheelchairAccessibleRoute = true
    
        // Get step by step directions
        venue?.navigate(directionsRequest, completion: { (navigationPath :LLNavigationPath?, error :Error?) in
            
            if (error != nil) {print ("navigation path unavailable ", error!.localizedDescription)}
            else {print("navigation path:", navigationPath!)}
        })
        
        // Get an eta for the route
        venue?.timeEstimate(directionsRequest, completion: { (estimate :NSNumber?, error :Error?) in
          
            if (error != nil) {print ("estimate unavailable ", error!.localizedDescription)}
            else {print("time estimate:", estimate!)}
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
    }
}

