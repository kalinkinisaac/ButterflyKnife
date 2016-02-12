//
//  BKTransform.cpp
//  ButterflyKnife
//
//  Created by Исаак Калинкин  on 12.02.16.
//  Copyright © 2016 BK. All rights reserved.
//

#include "BKTransform.hpp"
//==-Vector-===============================
BKVector2d::BKVector2d()
{
    *x = 0;
    *y = 0;
}
BKVector2d::BKVector2d(double _x, double _y)
{
    *x = _x;
    *y = _y;
}
BKVector2d::BKVector2d(BKVector2d &vector)
{
    *x = *vector.x;
    *y = *vector.y;
}
BKVector2d::~BKVector2d()
{
    delete x;
    delete y;
}
//==-Rotation-=============================
BKRotation::BKRotation(BKRotation &rotation)
{
    *x = *rotation.x;
    *y = *rotation.y;
}
//==-Transform-============================
BKTransform::BKTransform()    {
    position = new BKVector2d;
    rotation = new BKRotation;
    Layer = 0;
}
BKTransform::BKTransform(BKVector2d pos, BKRotation rot, int lay)
{
    *position = pos;
    *rotation = rot;
    Layer = lay;
}
BKTransform::~BKTransform()
{
    delete position;
    delete rotation;
}
