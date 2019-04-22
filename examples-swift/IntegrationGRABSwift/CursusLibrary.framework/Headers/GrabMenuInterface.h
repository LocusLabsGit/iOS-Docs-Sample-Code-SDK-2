//
//  GrabMenuInterface.h
//  CursusLibrary
//
//  Created by Jarod Velasquez on 7/27/16.
//  Copyright © 2016 Cursus. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol GrabMenuManagerDelegate <NSObject>

-(void)menuWillMakeSelection:(NSString *)selection;
-(void)airportChange:(NSDictionary *)dictAirport;
-(void)orderHistorySelected:(NSDictionary *)dictOrder;
-(void)favoriteOrderSelected:(NSDictionary *)dictOrder;
-(void)introScreenPresented;

@end

@protocol GrabMenuInterface <NSObject>

-(BOOL)menuEnabled;
-(BOOL)menuVisible;
-(void)initAndAddMenuToRootView:(UIView *)rootView withNavigationController:(UINavigationController *)navController;
-(void)animateMenuVisibilityChangeWithMainView:(UIView *)mainView andMainLeftConstraint:(NSLayoutConstraint *)mainLeftConstraint andMainRightConstraint:(NSLayoutConstraint *)mainRightConstraint;
-(void)resizeMenuWithHeightOffset:(int)heightOffset;
-(void)setMenuDelegate:(id<GrabMenuManagerDelegate>)delegate;

@end
