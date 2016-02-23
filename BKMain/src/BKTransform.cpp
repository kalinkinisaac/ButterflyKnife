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
BKVector2d::BKVector2d(double _x, double _y) {
	Set(_x, _y);
}
BKVector2d::BKVector2d(const BKVector2d &vector) {
	*this = vector;
}

BKVector2d* BKVector2d::Set(double _x, double _y) {
    x(_x);
    y(_y);
    return this;
}


double BKVector2d::GetLength()
{
    return sqrt(pow(this->x(), 2) + pow(this->y(), 2));
}
//Operators section
BKVector2d& operator + (BKVector2d lhs, BKVector2d rhs){
    return *new BKVector2d(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}
BKVector2d& BKVector2d::operator += (BKVector2d rhs){
    this->x(this->x() + rhs.x());
    this->y(this->y() + rhs.y());
    return *this;
}

BKVector2d& operator * (BKVector2d lhs, double rhs){
    return *new BKVector2d(lhs.x() * rhs, lhs.y() * rhs);
}

BKVector2d& operator * (double lhs, BKVector2d rhs){
    return (rhs * lhs);
}

BKVector2d& BKVector2d::operator *= (double rhs){
    //this->x(this->x()*rhs);
    //this->y(this->y()*rhs);
    *this = *new BKVector2d(*this * rhs);
    return *this;
}

BKVector2d& BKVector2d::operator= (BKVector2d rhs) {
    x(rhs.x());
    y(rhs.y());
    return *this;
}

bool operator==(BKVector2d lhs, BKVector2d rhs) {
	return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y()); 
}
//==-Rotation-=============================
BKRotation::BKRotation()
{
    this->direction = *new BKVector2d(0, 1);
}
BKRotation::BKRotation(BKVector2d direction)
{
    direction =  *new BKVector2d(direction.x()/direction.GetLength(),
                           direction.y()/direction.GetLength());
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
BKRotation::BKRotation(const BKRotation &rotation)
{
    *this = rotation;
}
BKRotation& operator+(BKRotation &lhs, BKRotation &rhs)
{
    /*
     X = x1*y2 + y1*x2
     Y = y1*y2 - x1*x2
     */
    return *new BKRotation(lhs.direction.x()*rhs.direction.y() + lhs.direction.y()*rhs.direction.x(),
                           lhs.direction.y()*rhs.direction.y() - lhs.direction.x()*rhs.direction.x());
}
BKRotation& BKRotation::operator+=(BKRotation& rhs)
{
    *this = *new BKRotation(*this + rhs);
    return *this;
}

//==-Transform-============================
BKTransform::BKTransform()  {	
    this->childCount = 0;

}
BKTransform::BKTransform(BKVector2d position, BKRotation rotation)
{
    SetLocalPosition(position);
    SetLocalRotation(rotation);
}
BKVector2d& BKTransform::GetPosition()
{
    return this->position;
}
BKVector2d& BKTransform::GetLocalPosition()
{
    return this->localPosition;
}
BKRotation& BKTransform::GetRotation()
{
    return this->rotation;
}
BKRotation& BKTransform::GetLocalRotation()
{
    return this->localRotation;
}
void BKTransform::SetLocalPosition(BKVector2d _localPosition)
{
    this->localPosition = _localPosition;
    this->UpdateTransform();
}
void BKTransform::SetLocalRotation(BKRotation _localRotation)
{
    this->localRotation = _localRotation;
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
        BKRotation pos_direction = *new BKRotation(this->localPosition);
        //Берем, получаем направление, в котором будет находиться наш обьект
        this->position = (parent->GetRotation() + pos_direction).direction;
        
        this->position *= this->localPosition.GetLength(); //Получаем полный вектор, домножая на длину
        
        this->position = parent->position + this->localPosition;//параллельный перенос
        
        
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
	this->children.push_back(child);
}
BKTransform *BKTransform::GetChild(unsigned long index)
{
    if(index < this->children.size())
       return this->children[index];
    else
       return new BKTransform;// error
}

BKTransform *BKTransform::GetParent() {
	return this->parent;
}

void BKTransform::DetachChildren()
{
	this->children.clear();
}
void BKTransform::RemoveChild(BKTransform *child){
	for(unsigned long i = 0; i < this->children.size(); ++i)
        if(children[i] == child)
        {
            this->children.erase(this->children.begin()+i);
        }

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


