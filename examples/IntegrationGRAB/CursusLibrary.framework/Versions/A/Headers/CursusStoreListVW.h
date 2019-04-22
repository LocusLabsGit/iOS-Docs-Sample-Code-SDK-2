//
//  CursusStoreListVW.h
//  CursusLibrary
//
//  Created by Michael Natale on 2/4/15.
//  Copyright (c) 2015 Cursus. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CursusStoreListVW : UITableView <UITableViewDataSource, UITableViewDelegate>

@property (nonatomic, strong) NSMutableDictionary *dictCursus;
@property (nonatomic, strong) NSMutableArray *arrStores;
@property (nonatomic, strong) NSMutableDictionary *dictStoreFrontImages;
@property (nonatomic, strong) NSString *shoppingCategory;

-(void)addtarget:(id)target action:(SEL)method;



@end
