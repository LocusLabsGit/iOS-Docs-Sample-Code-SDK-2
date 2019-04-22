//
//  VWSortFilterStore.h
//  Cursus
//
//  Created by Michael Natale on 5/13/14.
//  Copyright (c) 2014 Cursus. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CursusSortFilterStoreVW : UIView <UITableViewDelegate, UITableViewDataSource>

-(void)refreshCursusData:(NSString*)categoryType;
-(void)addtarget:(id)target action:(SEL)method;
-(void)resizeToFit;
-(void)setFilterTypeToFood:(BOOL)_bFilterFood;
-(void)clearSavedFilters;
-(id)initWithFrame:(CGRect)frame andTerminalID:(int)terminalID;
-(void)setFrame:(CGRect)frame andTerminalID:(int)terminalID;
-(void)setToTerminalFilter;

@end
