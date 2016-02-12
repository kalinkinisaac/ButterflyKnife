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
enum Space {World, Local};
class BKVector2d{
public:
    double *x, *y;
    BKVector2d()
    {
        *x = 0;
        *y = 0;
    }
    BKVector2d(double _x, double _y)
    {
        *x = _x;
        *y = _y;
    }
    ~BKVector2d()
    {
        delete x;
        delete y;
    }
    //BKVector2d operator = (BKVector2d b);
};

class BKTransform{
public:
    BKVector2d *position;
    BKVector2d *rotation;
    int Layer;
    BKTransform()
    {
        position = new BKVector2d;
        rotation = new BKVector2d;
        Layer = 0;
    }
    BKTransform(BKVector2d pos, BKVector2d rot, int lay)
    {
        *position = pos;
        *rotation = rot;
        Layer = lay;
    }
    ~BKTransform()
    {
        delete position;
        delete rotation;
    }
    void Rotate(BKVector2d rotation_to, Space space);
    void Move(BKVector2d position_to, Space space);
};

#endif /* BKTransform_hpp */
