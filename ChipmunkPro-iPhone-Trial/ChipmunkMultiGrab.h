#import "ObjectiveChipmunk.h"

@interface ChipmunkGrab : NSObject<ChipmunkObject> {
	NSArray *_chipmunkObjects;
	
	cpVect _pos;
	cpFloat _smoothing;
	
	ChipmunkShape *_grabbedShape;
	
	id _data;
}

/// Last touch location of the grab.
@property(nonatomic, readonly) cpVect pos;

/// The ChipmunkShape that this grab was created for.
@property(nonatomic, readonly) ChipmunkShape *grabbedShape;

/// User definable pointer
@property(nonatomic, retain) id data;

@end


/// Simple class to implement multitouch grabbing of physics objects.
@interface ChipmunkMultiGrab : NSObject {
	ChipmunkSpace *_space;
	NSMutableArray *_grabs;
	
	cpFloat _smoothing;
	cpFloat _grabForce;
	
	cpFloat _grabFriction;
	cpFloat _grabRotaryFriction;
	cpFloat _grabRadius;
	
	cpLayers _layers;
	cpGroup _group;
	bool (^_grabFilter)(ChipmunkShape *shape);
	
	bool _pushMode, _pullMode;
	
	cpFloat _pushMass;
	cpFloat _pushFriction;
	cpFloat _pushElasticity;
	cpCollisionType _pushCollisionType;
}

@property(nonatomic, assign) cpFloat smoothing;
@property(nonatomic, assign) cpFloat grabForce;

/// Layers used for the point query when grabbing objects.
@property(nonatomic, assign) cpLayers layers;

/// Group used for the point query when grabbing objects
@property(nonatomic, assign) cpGroup group;

/// Gives you the opportunity to further filter shapes. Return FALSE to ignore a shape.
/// The default implementation always returns TRUE.
@property(nonatomic, copy) bool (^grabFilter)(ChipmunkShape *shape);

/// Amount of friction applied by the touch.
/// Should be less than the grabForce. Defaults to 0.0.
@property(nonatomic, assign) cpFloat grabFriction;

/// The amount torque to apply to the grab to keep it from spinning.
/// Defaults to 0.0.
@property(nonatomic, assign) cpFloat grabRotaryFriction;

/// On a touch screen, a single point query can make it really hard to grab small objects with a fat finger.
/// By providing a radius, it will make it much easier for users to grab objects.
/// Defaults to 0.0.
@property(nonatomic, assign) cpFloat grabRadius;

@property(nonatomic, assign) bool pullMode;
@property(nonatomic, assign) bool pushMode;

@property(nonatomic, assign) cpFloat pushMass;
@property(nonatomic, assign) cpFloat pushFriction;
@property(nonatomic, assign) cpFloat pushElasticity;
@property(nonatomic, assign) cpCollisionType pushCollisionType;

@property(nonatomic, readonly) NSArray *grabs;


/**
	@c space is the space to grab shapes in.
	@c smoothing is the amount of mouse smoothing to apply as percentage of remaining error per second.
	cpfpow(0.8, 60) is a good starting point that provides fast response, but smooth mouse updates.
	@c force is the force the grab points can apply.
*/
-(id)initForSpace:(ChipmunkSpace *)space withSmoothing:(cpFloat)smoothing withGrabForce:(cpFloat)grabForce;

/// Start tracking a new grab point
/// Returns the ChipmunkGrab that is tracking the touch, but only if a shape was grabbed.
/// Returns nil when creating a push shape (if push mode is enabled), or when no shape is grabbed.
-(ChipmunkGrab *)beginLocation:(cpVect)pos;

/// Update a grab point.
/// Returns the ChipmunkGrab that is tracking the touch, but only if the grab is tracking a shape.
-(ChipmunkGrab *)updateLocation:(cpVect)pos;

/// End a grab point.
/// Returns the ChipmunkGrab that was tracking the touch, but only if the grab was tracking a shape.
-(ChipmunkGrab *)endLocation:(cpVect)pos;

@end
