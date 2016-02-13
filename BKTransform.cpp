//
//  BKTransform.cpp
//  ButterflyKnife
//
//  Created by Исаак Калинкин  on 12.02.16.
//  Copyright © 2016 BK. All rights reserved.
//

#include "BKTransform.hpp"
#include <vector>
using namespace std;
//==-Vector-===============================
BKVector2d::BKVector2d()
{
    x = 0;
    y = 0;
}
BKVector2d::BKVector2d(double _x, double _y)
{
    x = _x;
    y = _y;
}
BKVector2d::BKVector2d(BKVector2d &vector)
{
    x = vector.x;
    y = vector.y;
}
/*
BKVector2d::BKVector2d operator + (BKVector2d b){
    return *new BKVector2d;
}*/
//==-Rotation-=============================
BKRotation::BKRotation()
{
    x = 0;
    y = 0;
}
BKRotation::BKRotation(double _x, double _y)
{
    x = _x;
    y = _y;
}
BKRotation::BKRotation(BKRotation &rotation)
{
    x = rotation.x;
    y = rotation.y;
}
//==-Transform-============================
BKTransform::BKTransform()    {
    localPosition = *new BKVector2d;
    position = *new BKVector2d;
    rotation = *new BKRotation;
    Layer = 0;
}
BKTransform::BKTransform(BKVector2d pos, BKRotation rot, int lay)
{
    position = pos;
    rotation = rot;
    Layer = lay;
}

void BKTransform::AddChild(BKTransform child){
    BKTransform *temp = new BKTransform[++childCount];
    for(int i = 0; i < childCount - 1; i++)
        temp[i] = children[i];
    delete[] children;
    children = temp;
}
void BKTransform::RemoveChild(int id){
    if((id < 0) || (id >= childCount) || (childCount <= 0))
    {
        //lol error
    }
    else
    {
        BKTransform *temp = new BKTransform[--childCount];
        for(int i = 0; i < childCount - 1; i++)
            temp[i] = children[i];
        delete[] children;
        children = temp;

        childCount--;
    }
}
void BKTransform::AddParent(BKTransform _parent)
{
    parent = &_parent;
    position =  _parent.position + localPosition;
}


