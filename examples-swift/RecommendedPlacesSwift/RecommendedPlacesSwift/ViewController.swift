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
        
        // Enable recommended places
        LLConfiguration.shared().recommendedPlacesEnabled = true
        
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
    
    // MARK: Custom
    func customRecommendedPlaces() -> [Any] {
        
        var customRecommendedPlaces = [Any]()
        
        // Create a custom Recommended Place to show a POI
//        let ui = LLPlaceUI.default()
//        ui?.icon = "map-icon-airports.png"  // Supply any solid fill png. This one chosen as it is already in the bundle - you can supply your own
//        ui?.normalIconColor = UIColor.white
//        ui?.selectedIconColor = UIColor.white
//
//        // POI 519 is gate 68A at lax
//        let customPOIRecommendedPlace = LLPlace(behavior: .POI, values: ["519"], displayName: "Departure Gate", andUI: ui)
//        customRecommendedPlaces.append(customPOIRecommendedPlace as Any)
        
        // Create a custom Recommended Place to trigger a search
        let uiSearch = LLPlaceUI.default()
        uiSearch?.icon = "map-icon-airports.png"  // Supply any solid fill png. This one chosen as it is already in the bundle - you can supply your own
        uiSearch?.normalIconColor = UIColor.white
        uiSearch?.selectedIconColor = UIColor.white
        uiSearch?.marker = "images/pin-plane-landing.svg"; // Supply any size-embedded svg of your choice. This ins chosen as it is already in the bundle
        
        let customSearchRecommendedPlace = LLPlace(behavior: .search, values: ["magazines"], displayName: "Magazines", andUI: uiSearch)
        customRecommendedPlaces.append(customSearchRecommendedPlace as Any)
        
        return customRecommendedPlaces
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
        
        // Show only 1 recommended place
//        if let firstPlace = places?[0] {
//
//            return [firstPlace]
//        }
//        else {
//
//            return places
//        }
        
        // Show default recommended places
//         return places;
        
        // Show only the tray button (when tapped - it will open the tray showing all recommended places)
//        var nullFirstArray = [Any]()
//        nullFirstArray.append(NSNull())
//        nullFirstArray.append(contentsOf: places)
//        return nullFirstArray
        
        // Show custom recommended places
        return customRecommendedPlaces()
    }
    
    func mapView(_ mapView: LLMapView!, willPresentSearchSuggestions suggestions: [String]!) -> [String]! {
        
        return ["Restaurants", "Bars", "Pharmacies", "Baggage"]
    }
}

