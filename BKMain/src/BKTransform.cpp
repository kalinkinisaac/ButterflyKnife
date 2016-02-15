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

void BKVector2d::x(double _x) {
    this->X = _x;
 
}
void BKVector2d::y(double _y) {
    this->Y = _y;
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
    this->direction = *new BKVector2d();
}
BKRotation::BKRotation(double _x, double _y)
{
    this->direction = *new BKVector2d(_x, _y);
}
BKRotation::BKRotation(BKRotation &rotation)
{
    this->direction = *new BKVector2d(rotation.direction);
}
//==-Transform-============================
BKTransform::BKTransform()    {
    this->localPosition = *new BKVector2d;
    this->position = *new BKVector2d;
    this->rotation = *new BKRotation;
   
}
BKTransform::BKTransform(BKVector2d position, BKRotation rotation)
{
    setPosition(position);
    setRotation(rotation);
}

void BKTransform::setPosition(BKVector2d position)
{
    this->position = position;
    ChildReTransform();
}
void BKTransform::setRotation(BKRotation rotation)
{
    this->rotation = rotation;
    ChildReTransform();
}
void BKTransform::Rotate(double angle, Space space)
{
    if(space == World)
    {
        //rotate
    }
    else
    {
        
    }
}
void BKTransform::Move(BKVector2d position_to, Space space)
{
    if(space == World)
    {
        position += position_to;
    }
    else
    {
        localPosition += position_to;
    }
    //needs to operator overload

}

void BKTransform::ChildReTransform()
{
    BKTransform *ptr = *children;
    for(int i = 0; i < childCount; i++, ptr++){
        //jopa-math position update
        double leng = sqrt(pow(this->rotation.direction.x(),2)
                         + pow(this->rotation.direction.y(),2));
        double sin1 = this->rotation.direction.x()/leng;
        double cos1 = this->rotation.direction.y()/leng;
        ptr->position.x(ptr->localPosition.x()*cos1
                      + ptr->localPosition.y()*sin1);
        ptr->position.y(-ptr->localPosition.x()*sin1
                        + ptr->localPosition.y()*cos1);
        //rotation update
        ptr->rotation.direction.x(ptr->localRotation.direction.x()*cos1
                        + ptr->localRotation.direction.y()*sin1);
        ptr->rotation.direction.y(-ptr->localRotation.direction.x()*sin1
                                  + ptr->localRotation.direction.y()*cos1);
        //^^^^this code needs check^^^^^^
        ptr = ++ptr;
    }
}
void BKTransform::AddChild(BKTransform *child){
    BKTransform **temp = new BKTransform*[++this->childCount];
    for(int i = 0; i < childCount - 1; i++)
        temp[i] = children[i];
    temp[childCount - 1] = child;
    free(children);
    children = temp;
}

void BKTransform::RemoveChild(BKTransform *child){
    int child_id;
        for(int i = 0; i < childCount; i++)
            if(children[i] == child)
                child_id = i;
    BKTransform *ptr = *children;
        for(int i = child_id; i < childCount - 1; i++, ptr++)
            ptr = ++ptr;
    delete ptr;
    //неплохо сыграно
}



void BKTransform::SetParent(BKTransform parent)
{
    this->parent = &parent;
    parent.AddChild(this);
    //jopa_math begin
    int a;
}
void BKTransform::deleteParent()
{
    parent->RemoveChild(this);
    delete this->parent;
    //без родителя localPosition - то же, что и position
    this->position = this->localPosition;
}


