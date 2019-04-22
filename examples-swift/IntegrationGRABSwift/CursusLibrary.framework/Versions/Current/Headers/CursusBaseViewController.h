//
//  CursusBaseViewController.h
//  CursusLibrary
//
//  Created by Jarod Velasquez on 4/3/16.
//  Copyright © 2016 Cursus. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface CursusBaseViewController : UIViewController

@property (nonatomic, weak) UIView *activeField;
@property (nonatomic, weak) UIScrollView *vwMainScroll;

-(void)popToRootGrabController;
//-(void)removeGrabVCsFromViewControllerArray;
-(void)popAllGrabControllers;
-(void)removeGrabVCsFromViewControllerArrayAndAddVC:(UIViewController *)viewToAdd removeRootGrabVC:(BOOL)removeRootGrabVC;
-(int)getIndexOfFirstGrabVC;
-(BOOL)isRootGrabVC;
- (void)registerForKeyboardNotifications;
-(void)restorePreviousAppearance;

@end
