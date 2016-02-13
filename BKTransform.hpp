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
#include <cmath>
#include <vector>
enum Space {World, Local};
namespace bk_tr {


class BKVector2d{
public:
    double x, y;
    BKVector2d();
    BKVector2d(double _x, double _y);
    BKVector2d(BKVector2d &vector);
    ~BKVector2d();

};
    double Distanse(BKVector2d &a, BKVector2d &b);
    BKVector2d operator + (BKVector2d b);
class BKRotation : BKVector2d{
public:
    double x, y;
    BKRotation();
    BKRotation(double _x, double _y);
    BKRotation(BKRotation &rotation);
    void SetLookRotation(BKVector2d target);
    int Angle(BKRotation &a, BKRotation &b);
};
class BKTransform{
private:
    void increment_child();
public:
    BKTransform *parent; std::vector<BKTransform> children;
    BKVector2d position, localPosition;
    BKRotation rotation;
    int Layer;
    int childCount = 0;
    BKTransform();
    BKTransform(BKVector2d pos, BKRotation rot, int lay);
    void Rotate(BKVector2d rotation_to, Space space);
    void Move(BKVector2d position_to, Space space);
    void AddChild(BKTransform child);
    void RemoveChild(int id);
};
}
#endif /* BKTransform_hpp */
