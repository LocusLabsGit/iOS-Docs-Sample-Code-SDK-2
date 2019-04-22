//
//  CursusFilterModalVW.h
//  CursusLibrary
//
//  Created by Wade Williams on 7/2/17.
//  Copyright © 2017 Cursus. All rights reserved.
//


#import <UIKit/UIKit.h>

@interface CursusFilterModalVW : UIView
- (id)initWithFrame:(CGRect)frame andTarget:(id)target andSelectorForOK:(SEL)selector andTerminal:(NSString*)terminal andFilterButtonFrame:(CGRect)filterButtonFrame;
//- (id)initWithFrame:(CGRect)frame andTarget:(id)target andSelectorForOK:(SEL)selector andTerminal:(NSString*)terminal;
//-(void)setFrame:(CGRect)frame andTerminalID:(int)terminalID;
@end
