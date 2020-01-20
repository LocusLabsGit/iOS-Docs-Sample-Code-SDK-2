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
        mapView?.showTopSafeAreaOverlay = false
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
    
    // MARK: Custom
    func customActions() -> [Any] {
        
        var customActions = [Any]()
        
        // Create a custom action to show a POI
        let ui = LLPlaceUI.default()
        ui?.icon = "map-icon-airports.png"  // Supply any solid fill png. This one chosen as it is already in the bundle - you can supply your own
        ui?.normalIconColor = UIColor.orange

        // POI 519 is gate 68A at lax
        let customPOIAction = LLPlace(behavior: .POI, values: ["519"], displayName: "Departure Gate", andUI: ui)
        customActions.append(customPOIAction as Any)
        
        // Create a custom action to trigger a search
        let uiSearch = LLPlaceUI.default()
        uiSearch?.icon = "map-icon-airports.png"  // Supply any solid fill png. This one chosen as it is already in the bundle - you can supply your own
        uiSearch?.normalIconColor = UIColor.white
        uiSearch?.marker = "images/pin-plane-landing.svg"; // Supply any size-embedded svg of your choice. This is chosen as it is already in the bundle
        
        let customSearchAction = LLPlace(behavior: .search, values: ["check-in"], displayName: "Check-In", andUI: uiSearch)
        customActions.append(customSearchAction as Any)
        
        return customActions
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
    
    func mapView(_ mapView: LLMapView!, willPresentPlaces places: [Any]!) -> [Any]! {
        
        // Show only 1 action
//        if let firstPlace = places?[0] {
//
//            return [firstPlace]
//        }
//        else {
//
//            return places
//        }
        
        // Show default actions
//         return places;
        
        // Show custom actions
        return customActions()
    }
}

