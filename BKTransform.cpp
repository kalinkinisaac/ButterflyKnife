//
//  BKTransform.cpp
//  ButterflyKnife
//
//  Created by Исаак Калинкин  on 12.02.16.
//  Copyright © 2016 BK. All rights reserved.
//

#include "BKTransform.hpp"
#include <vector>
#include <cmath>
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
    this->x = rotation.x;
    this->y = rotation.y;
}
//==-Transform-============================
BKTransform::BKTransform()    {
    this->localPosition = new BKVector2d;
    this->position = new BKVector2d;
    this->rotation = new BKRotation;
    this->layer = 0;
}
BKTransform::BKTransform(BKVector2d position, BKRotation rotation, int layer)
{
    *this->position = position;
    *this->rotation = rotation;
    this->layer = layer;
}
//don't work
void BKTransform::AddChild(BKTransform *child){
    BKTransform *temp = new BKTransform[++childCount];
    for(int i = 0; i < childCount - 1; i++)
        temp[i] = children[i];
    //temp[childCount - 1] = child;
    delete[] children;
    children = temp;
}
//mb don't work
void BKTransform::RemoveChild(BKTransform *child){
    int child_id;
        for(int i = 0; i < childCount; i++)
            if(&children[i] == child)
                child_id = i;
    BKTransform *ptr = children;
        for(int i = child_id; i < --childCount; i++, ptr++)
            ptr = ++ptr;
    delete ptr;

}
void BKTransform::SetParent(BKTransform parent)
{
    this->parent = &parent;
    parent.AddChild(this);
    //здесь должно быть изменение позиции с соответствием  трансформа родителя
    //this->position =  parent.position + localPosition;
}
void BKTransform::deleteParent()
{
    parent->RemoveChild(this);
    delete this->parent;
    //без родителя localPosition - то же, что и position
    this->position = localPosition;
}


