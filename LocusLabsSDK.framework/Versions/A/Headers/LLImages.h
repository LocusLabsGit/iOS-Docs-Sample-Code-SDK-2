//
//  LLImages.h
//  LocusLabsSDK
//
//  Created by Glenn Dierkes on 3/15/17.
//  Copyright © 2017 LocusLabs. All rights reserved.
//

@interface LLImages : NSObject


/**
 * Returns the URL for the given image.
 */
+(NSURL*)getImageURL:(NSString*)imageName;


/**
 * Returns the URL for the given image with the given width and height.
 * The aspect ratio will be retained and each dimension with be the given value or less.
 */
+(NSURL*)getImageURL:(NSString*)imageName forWidth:(int)width andHeight:(int)height;


/**
 * Returns the URL for the given image with the given width and height.
 * The image will be center cropped.
 */
+(NSURL*)getImageURLCenterCrop:(NSString*)imageName forWidth:(int)width andHeight:(int)height;


@end
