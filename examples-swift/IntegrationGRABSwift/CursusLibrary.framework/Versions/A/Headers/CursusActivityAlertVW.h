//
//  CursusActivityAlertVW.h
//  CursusLibrary
//
//  Created by Michael Natale on 2/5/15.
//  Copyright (c) 2015 Cursus. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CursusActivityAlertVW : UIAlertView
{
    UIActivityIndicatorView *m_actMonitor;
}

+ (CursusActivityAlertVW *)singleton;
- (void) showInView;
- (void) hideInView;

@property (nonatomic, strong) UIActivityIndicatorView *ActMonitor;

@end
