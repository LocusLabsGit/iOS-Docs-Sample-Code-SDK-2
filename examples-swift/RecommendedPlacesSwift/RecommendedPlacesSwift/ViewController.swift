//
//  ViewController.swift
//  ShowFullScreenMapSwift
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

import UIKit

class ViewController: UIViewController, LLVenueDatabaseDelegate, LLFloorDelegate, LLMapViewDelegate {

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
        
        LLConfiguration.shared().recommendedPlacesEnabled = true
        
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
    func customRecommendedPlaces() -> [Any] {
        
        var customRecommendedPlaces = [Any]()
        
        // Create a custom Recommended Place to show a POI
        let ui = LLPlaceUI.default()
        ui?.icon = "bottombar-icon-nav.png"
        ui?.normalIconColor = UIColor.white
        ui?.selectedIconColor = UIColor.white
        ui?.marker = "images/nav-badge-bus.svg"
        
        // POI 519 is gate 68A at lax
        let customPOIRecommendedPlace = LLPlace(behavior: .POI, values: ["519"], displayName: "Departure Gate", andUI: ui)
        customRecommendedPlaces.append(customPOIRecommendedPlace as Any)
        
        // Create a custom Recommended Place to trigger a search
//        let customSearchRecommendedPlace = LLPlace(behavior: .search, values: ["magazines"], displayName: "Magazines", andUI: ui)
//        customRecommendedPlaces.append(customSearchRecommendedPlace as Any)
        
        return customRecommendedPlaces
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
        // return places;
        
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

