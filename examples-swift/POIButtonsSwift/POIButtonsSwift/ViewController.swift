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
    
    // MARK: Delegates - LLVenueDatabase
    func venueDatabase(_ venueDatabase: LLVenueDatabase!, venueLoadFailed venueId: String!, code errorCode: LLDownloaderError, message: String!) {
        
        // Handle failures here
    }
    
    // MARK: Delegates - LLMapView
    func mapViewDidClickBack(_ mapView: LLMapView!) {
        
        // The user tapped the "Cancel" button while the map was loading. Dismiss the app or take other appropriate action here
    }
    
    func mapViewReady(_ mapView: LLMapView!) {
        
        // Show POI 870, which is the Starbucks near gate 60 at LAX - you can find POI IDs using our Venue Management System (VMS) or by imlpementing the "didTapPOI" delegate method
        mapView?.showPoi(byPoiId: "870")
    }
    
    func mapView(_ mapView: LLMapView!, additionalViewsForPOI poiId: String!) -> [Any]! {
        
        var additionalViews = [Any]()
        
        // Only add extra buttons for the Starbucks POI
        if poiId == "870" {
            
            let button1 = LLIconButton.topIconButton(withPadding: 0, image: UIImage(named: "custom_icon_1.png"), andLabel: "Custom1")
            additionalViews.append(button1 as Any)
            
            button1?.addTarget(self, action: #selector(customPoiButtonTapped), for: .touchUpInside)
        }
        
        return additionalViews
    }
    
    @objc func customPoiButtonTapped() {
        
        print("Custom POI Button tapped")
    }
}

