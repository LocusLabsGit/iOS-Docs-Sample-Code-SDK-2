//
//  ViewController.swift
//  UICustomizationSwift
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
            
            self.venue = _venue
        }
    }

    // MARK: Custom
    func themeWithCustomBottomBar() -> LLTheme {
        
        let themeBuilder = LLThemeBuilder(theme: LLTheme.default())
        themeBuilder.setProperty("MapView.BottomBar.backgroundColor", value: UIColor.orange)
        themeBuilder.setProperty("MapView.BottomBar.Button.Title.textColor", value: UIColor.black)
        
        return themeBuilder.theme
    }
    
    func themeWithCustomFont(customFont: UIFont) -> LLTheme {
        
        let themeBuilder = LLThemeBuilder(theme: LLTheme.default())
        themeBuilder.setProperty("fonts.normal", value: customFont)
        
        return themeBuilder.theme
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
        
        // Change the font
        // mapView?.theme = themeWithCustomFont(customFont: UIFont(name: "American Typewriter", size: 12)!)
        
        // Set a custom back button title
        //mapView?.setBackButtonText(NSLocalizedString("Back", comment: ""))
        
        // Change the search bar background color
        //mapView?.setSearchBarBackgroundColor(UIColor.orange)
        
        // Change the bottom bar background and button title colors
        mapView?.theme = themeWithCustomBottomBar()
    }
}

