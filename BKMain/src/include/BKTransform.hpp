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
    BKVector2d operator + (BKVector2d b);
    BKVector2d operator += (BKVector2d b);
};
    double Distanse(BKVector2d &a, BKVector2d &b);

class BKRotation {
    
public:
    BKVector2d direction;
    BKRotation();
    BKRotation(double _x, double _y);
    BKRotation(BKRotation &rotation);
    void SetLookRotation(BKVector2d target);
    int Angle(BKRotation &a, BKRotation &b);
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
    void ChildReTransform();
public:
    
    BKTransform();
    BKTransform(BKVector2d pos, BKRotation rot);
    //basics
    BKVector2d getPosition();
    void setPosition(BKVector2d position);
    BKRotation getRotation();
    void setRotation(BKRotation rotation);
    
    int getLayer();
    void setLayer(int l);
    
    void Rotate(double angle, Space space);//повернуть на angle радиан
    void Move(BKVector2d position_to, Space space);//переместить на вектор
    
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
