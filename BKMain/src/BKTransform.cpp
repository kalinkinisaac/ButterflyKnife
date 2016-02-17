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
BKVector2d& BKVector2d::GetUnitVector2d()
{
    double _x = x();
    double _y = y();
    return *new BKVector2d(this->x()/GetLength(),
                           this->y()/GetLength());
}
double BKVector2d::GetLength()
{
    return sqrt(pow(this->x(), 2) + pow(this->y(), 2));
}

BKVector2d& BKVector2d::operator + (BKVector2d& b){
    //return *new BKVector2d;
}
BKVector2d& BKVector2d::operator += (BKVector2d& b){
}
BKVector2d& BKVector2d::operator * (double k){
}
BKVector2d& BKVector2d::operator *= (double k){
}
//==-Rotation-=============================
BKRotation::BKRotation()
{
    this->direction = *new BKVector2d(0, 1);
}
BKRotation::BKRotation(BKVector2d direction)
{
    this->direction = direction;
}
BKRotation::BKRotation(double _x, double _y)
{
    if((_x == 0)&&(_y == 0))
        BKRotation(0, 1);
    else
        this->direction = *new BKVector2d(_x/sqrt(_x*_x+_y*_y),
                                          _y/sqrt(_x*_x+_y*_y));
}
BKRotation::BKRotation(BKRotation &rotation)
{
    this->direction = *new BKVector2d(rotation.direction);
}
BKRotation& BKRotation::operator+(BKRotation& rotation)
{
    
}
BKRotation& BKRotation::operator+=(BKRotation& rotation)
{
    
}

//==-Transform-============================
BKTransform::BKTransform()    {
    this->position = *new BKVector2d;
    this->localPosition = *new BKVector2d;
    this->rotation = *new BKRotation;
    this->localRotation = *new BKRotation;
   
}
BKTransform::BKTransform(BKVector2d position, BKRotation rotation)
{
    SetLocalPosition(position);
    SetLocalRotation(rotation);
}
BKVector2d BKTransform::GetPosition()
{
    return this->position;
}
BKVector2d BKTransform::GetLocalPosition()
{
    return this->localPosition;
}
BKRotation BKTransform::GetRotation()
{
    return this->rotation;
}
BKRotation BKTransform::GetLocalRotation()
{
    return this->localRotation;
}
void BKTransform::SetLocalPosition(BKVector2d localPosition)
{
    this->localPosition = position;
    this->UpdateTransform();
}
void BKTransform::SetLocalRotation(BKRotation localRotation)
{
    this->localRotation = rotation;
    this->UpdateTransform();
}
void BKTransform::Rotate(BKRotation deltaRotation)
{
    this->localRotation += deltaRotation;
}

void BKTransform::Rotate(double angle)
{

}
void BKTransform::Move(BKVector2d position_to)
{

    localPosition += position_to;
    //needs to operator overload
}

void BKTransform::UpdateTransform()
{
	if(parent == 0) {//а так можно?
		this->position = this->localPosition;
		this->rotation = this->localRotation;
	}
	else
    {
        //Position update
        
        //ротация, направленна на нашу позицию (единичная, как всегда)
        BKRotation pos_direction = *new BKRotation(this->localPosition.GetUnitVector2d());
        //Берем, получаем направление, в котором будет находиться наш обьект
        this->position = (parent->getRotation() + pos_direction).direction;
        
        this->position *= this->localPosition.GetLength(); //Получаем полный вектор, домножая на длину
        
        this->position += parent->position;//параллельный перенос
        
        
        //Rotation update
        
        this->rotation = parent->rotation + this->localRotation;
        
        /* Как я и говорил, BKVector и BKRotation совершенно разные вещи:
           на данном этапе operator + у BKVector2d и BKRotation разные 
           (у BKVector это просто сложение соответствующих координат, а
            у BKRotation вычисляется по формуле) 
         PS. Осталось написать все operators, я еще хз как, но формулы есть*/
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
        for(int i = child_id; i < childCount - 1; i++)
            ptr = ++ptr;
    delete ptr;
}



void BKTransform::SetParent(BKTransform parent)
{
    this->parent = &parent;
    parent.AddChild(this);
}

void BKTransform::deleteParent()
{
    parent->RemoveChild(this);
    delete this->parent;
    //без родителя localPosition - то же, что и position
    this->position = this->localPosition;
}


