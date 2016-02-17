//
//  BKTransform.hpp
//  ButterflyKnife
//
//  Created by Исаак Калинкин  on 12.02.16.
//  Copyright © 2016 BK. All rights reserved.
//

#ifndef BKTransform_hpp
#define BKTransform_hpp

#include <SFML/Graphics.hpp>
enum Space {World, Local};
//namespace bk_tr {
class BKVector2d{
private:
    double X, Y;
public:
    double x();
    double y();
    void x(double _x);
    void y(double _y);
    BKVector2d();
    BKVector2d(double _x, double _y);
    BKVector2d(BKVector2d &vector);
    double GetLength();
    BKVector2d& operator + (BKVector2d& b);
    BKVector2d& operator += (BKVector2d& b);
    BKVector2d& operator * (double k);
    BKVector2d& operator *= (double k);
};
    double Distanse(BKVector2d &a, BKVector2d &b);

class BKRotation {
public:
    BKVector2d direction; //по идее единичный вектор
    BKRotation();
    BKRotation(BKVector2d direction);
    BKRotation(double _x, double _y);
    BKRotation(BKRotation &rotation);
    void Set(double x);
    void Set(BKRotation rotation);
    void SetFromToRotation(BKVector2d from, BKVector2d to);
    void SetLookRotation(BKVector2d target);//ротация, смотрящая
    double ToAngle();//angle betw OY and rotation
    BKRotation& operator + (BKRotation &rotation);
    BKRotation& operator += (BKRotation &rotation);

};
class BKTransform{
private:
    int id;
    BKTransform *parent;//трансформ родителя
    BKTransform **children;//массив дочерних обьектов трансформа
    BKVector2d position, localPosition;//позиции: глобальная и локальная(относительно родителя)
    BKVector2d forward; //направление "вперед" этого обьекта
    BKRotation rotation, localRotation;//ротация
    int childCount; //количество дочерних обьектов
    void UpdateTransform();//wow wow, slowly plz
public:
    
    BKTransform();
    BKTransform(BKVector2d pos, BKRotation rot);
    //basics
    BKVector2d GetPosition();
    BKVector2d GetLocalPosition();
    void SetLocalPosition(BKVector2d localPosition);
    BKRotation GetRotation();
    BKRotation GetLocalRotation();
    void SetLocalRotation(BKRotation localRotation);
    
    
    void Rotate(BKRotation deltaRotation);//повернуть НА ротацию
    void Rotate(double angle);//повернуть на angle радиан
    void Move(BKVector2d position_to);//переместить на вектор
    
    //parent section
    /*Всегда пользуемся для создания дочерних обьектов только этими функциями.
    //Например, чтобы сделать B дочерним к A, пишем B.SetParent(A)*/
    void SetParent(BKTransform parent);
    BKTransform GetParent();
    void deleteParent();
    
    //don't use it
    void RemoveChild(BKTransform *child);
    void AddChild(BKTransform *child);
};
//}
#endif /* BKTransform_hpp */
