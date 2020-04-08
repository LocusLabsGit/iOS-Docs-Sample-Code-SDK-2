//
//  ViewController.swift
//  ShowFullScreenMapSwift
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

import UIKit

class ViewController: UITableViewController, LLVenueDatabaseDelegate  {

    // Vars
    var venueDatabase:      LLVenueDatabase!
    
    var venues =             [LLVenueInfo]()
    
    // MARK: Lifecycle
    override func viewDidLoad() {
        
        super.viewDidLoad()
        
        title = "Venues"
        
        // Initialize the LocusLabs SDK with the accountId provided by LocusLabs
        LLLocusLabs.setup().accountId = "A11F4Y6SZRXH4X"
        
        // Get an instance of LLVenueDatabase, register as its delegate and load the venue LAX
        venueDatabase = LLVenueDatabase()
        venueDatabase.delegate = self
        
        // Load the venue LAX async
        venueDatabase.listVenues()
    }
    
    // MARK: Delegates - LLVenueDatabase
    func venueDatabase(_ venueDatabase: LLVenueDatabase!, venueLoadFailed venueId: String!, code errorCode: LLDownloaderError, message: String!) {
        
        // Handle failures here
    }
    
    func venueDatabase(_ venueDatabase: LLVenueDatabase!, venueList: [Any]!) {
        
        venues = venueList as! [LLVenueInfo]
        venues = venues.sorted(by: { (venue1, venue2) -> Bool in
            return venue1.name < venue2.name
        })
        
        tableView.reloadData()
    }
    
    // MARK: Delegates - TableView
    override func numberOfSections(in tableView: UITableView) -> Int {
        
        return 1
    }
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        
        return venues.count
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        var cell = tableView.dequeueReusableCell(withIdentifier: "Cell")
        
        if (cell == nil) {cell = UITableViewCell(style: .default, reuseIdentifier: "Cell")}
        
        let venueInfo = venues[indexPath.row]
        let airportCode = venueInfo.venueId.count > 3 ? String(venueInfo.venueId.prefix(3)) : venueInfo.venueId
        cell?.textLabel?.text = String.init(format: "%@ (%@)", venueInfo.name, airportCode!.uppercased())
        
        return cell!
    }
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
        tableView.deselectRow(at: indexPath, animated: true)
        
        let venueInfo = venues[indexPath.row]
        
        let mapController = MapController()
        mapController.venueID = venueInfo.venueId
        navigationController?.pushViewController(mapController, animated: true)
    }
    
}

