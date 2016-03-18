#ifndef BKCamera_hpp
#define BKCamera_hpp


#include "BKObject.hpp"
#include "BKTransform.hpp"

class BKCamera : public BKObject {
protected:
	BKVector2d Cam_Area;
public:
	BKVector2d CamArea();
	BKVector2d CamArea(BKVector2d NewArea);
	void SetAspectRatio(double ratio);
	void SetAspectRatio(double X, double Y);
	BKCamera();
	BKCamera(BKTransform Transform);
	BKCamera(BKVector2d NewArea);
	BKCamera(BKTransform Transform, BKVector2d NewArea);
};
#endif

