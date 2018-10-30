//
//  ViewController.swift
//  ShowFullScreenMapSwift
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

import UIKit

class ViewController: UIViewController, LLVenueDatabaseDelegate, LLMapViewDelegate, LLPOIDatabaseDelegate {

    // Vars
    var venueDatabase:      LLVenueDatabase!
    var venue:              LLVenue?
    var mapView:            LLMapView?
    var poiDatabase:        LLPOIDatabase?
    var customMarkers =     [LLMarker]()
    
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
            
            self.venue = _venue
        }
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
            customMarkers.append(marker)
        }
    }
}

