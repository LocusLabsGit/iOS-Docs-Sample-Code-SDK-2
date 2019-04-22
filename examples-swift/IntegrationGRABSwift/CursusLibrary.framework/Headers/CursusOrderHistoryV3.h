//
//  CursusOrderHistoryV3.h
//  CursusLibrary
//
//  Created by Sky on 11/6/17.
//  Copyright © 2017 Cursus. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CursusBaseViewController.h"


@interface CursusOrderHistoryV3 : CursusBaseViewController <UITableViewDelegate, UITableViewDataSource>

-(UIView*)getOrderDetailView:(NSMutableDictionary*)dictOrder orderIndex:(int)orderIndex parentView:(UIView*)parentView isActiveCard:(BOOL)isActiveCard;
-(id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil arrOrders:(NSArray *)arrOrders;
-(void)handleOrderDetailChange:(NSDictionary *)orderInfo;
-(void)setParentView:(UIView*)callingParentView;
-(void)setOrderArray:(NSMutableArray*)arrOrders;

@end
