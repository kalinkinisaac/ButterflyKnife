#include "include/BKCamera.hpp"

BKVector2d BKCamera::CamArea() {
	return this->Cam_Area;
}

BKVector2d BKCamera::CamArea(BKVector2d NewArea) {
	this->Cam_Area = NewArea;
	return this->Cam_Area;
}

void BKCamera::SetAspectRatio(double ratio) {
	this->Cam_Area.y(ratio * this->Cam_Area.x());
}

void BKCamera::SetAspectRatio(double X, double Y) {
	this->SetAspectRatio(Y/X);
}

BKCamera::BKCamera() : BKObject() {}

BKCamera::BKCamera(BKTransform Transform) : BKObject(Transform) {}

BKCamera::BKCamera(BKVector2d NewArea) {
	this->CamArea(NewArea);
}


BKCamera::BKCamera(BKTransform Transform, BKVector2d NewArea) : BKObject(Transform) {
	this->CamArea(NewArea);
}

