//
//  ViewController.swift
//  MapBasicsSwift
//
//  Created by Juan Kruger on 01/02/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

import UIKit

class ViewController: UIViewController, LLVenueDatabaseDelegate, LLMapViewDelegate {
    
    // Vars
    var venueDatabase:  LLVenueDatabase!
    var venue:          LLVenue?
    var mapView:        LLMapView?
    
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
        venueDatabase = LLVenueDatabase(mapView: mapView)
        venueDatabase.delegate = self
        
        // Load the venue LAX async
        venueDatabase.loadVenueAndMap("lax") { (_venue: LLVenue?, _map: LLMap?, _floor: LLFloor?, _marker: LLMarker?) in
            
            self.mapView?.map = _map
            self.venue = _venue
        }
    }
    
    // MARK: Custom
    @objc private func changeMapLevel() {
        
        // Change to building level 2 (ticketing). You can get level ids like the one below by calling "listFloors" on the current LLBuilding instance
        mapView?.levelSelected("lax-default-Ticketing")
    }
    
    private func positionAndZoomMap() {
        
        // Set the center of the map to Terminal 6 and zoom in. You can find lat/lng etc. either by logging into your VMS, or using the "didTapPOI" and "didTapAtPosition" delegate calls from LLMapView
        mapView?.mapCenter = LLLatLng(lat: 33.941384, lng: -118.402057)
        mapView?.mapRadius = 190.0
        
        perform(#selector(changeMapLevel), with: nil, afterDelay: 8)
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
        
        positionAndZoomMap()
    }
}

