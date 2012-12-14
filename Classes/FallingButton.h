#import <Foundation/Foundation.h>

#import "ObjectiveChipmunk.h"

@interface FallingButton : NSObject <ChipmunkObject> {
	UIButton *button;
	
	ChipmunkBody *body;
	NSArray *chipmunkObjects;
	
	int touchShapes;
}

@property (readonly) UIButton *button;
@property (readonly) NSArray *chipmunkObjects;
@property int touchedShapes;

- (void)updatePosition;

@end
