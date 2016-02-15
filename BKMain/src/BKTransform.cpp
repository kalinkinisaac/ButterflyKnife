//
//  BKTransform.cpp
//  ButterflyKnife
//
//  Created by Исаак Калинкин  on 12.02.16.
//  Copyright © 2016 BK. All rights reserved.
//

#include "include/BKTransform.hpp"
#include <vector>
#include <cmath>
using namespace std;
//==-Vector-===============================

double BKVector2d::x() {
	return this->X;
}

double BKVector2d::y() {
	return this->Y;
}

double BKVector2d::x(double _x) {
	this->X = _x;
	return this->X;
}

double BKVector2d::y(double _y) {
	this->Y = _y;
	return this->Y;
}

BKVector2d::BKVector2d()
{
    x(0); y(0);
}
BKVector2d::BKVector2d(double _x, double _y)
{
    x(_x);
    y(_y);
}
BKVector2d::BKVector2d(BKVector2d &vector)
{
    x(vector.x());
    y(vector.y());
}

/*
BKVector2d::BKVector2d operator + (BKVector2d b){
    return *new BKVector2d;
}*/
//==-Rotation-=============================
BKRotation::BKRotation()
{
    this->BK_ROTATION_DIRECTION = *new BKVector2d();
}
BKRotation::BKRotation(double _x, double _y)
{
    this->BK_ROTATION_DIRECTION = *new BKVector2d(_x, _y);
}
BKRotation::BKRotation(BKRotation &rotation)
{
    this->BK_ROTATION_DIRECTION = *new BKVector2d(rotation.BK_ROTATION_DIRECTION);
}
//==-Transform-============================
BKTransform::BKTransform()    {
    this->localPosition = new BKVector2d;
    this->position = new BKVector2d;
    this->rotation = new BKRotation;
   
}
BKTransform::BKTransform(BKVector2d position, BKRotation rotation)
{
    *this->position = position;
    *this->rotation = rotation;
}
//don't work
void BKTransform::AddChild(BKTransform *child){
    BKTransform **temp = new BKTransform*[++this->childCount];
    for(int i = 0; i < childCount - 1; i++)
        temp[i] = children[i];
    temp[childCount - 1] = child;
    free(children);
    children = temp;
}
//mb don't work
//
//FIX IT
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


