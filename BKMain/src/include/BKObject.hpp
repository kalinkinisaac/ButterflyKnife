//
//  BKObject.hpp
//  ButterflyKnife
//
//  Created by Исаак Калинкин  on 12.02.16.
//  Copyright © 2016 BK. All rights reserved.
//

#ifndef BKObject_hpp
#define BKObject_hpp
#include "BKTransform.hpp"
class BKObject{
private:
public:
    BKTransform *transform;
    BKVector2d p;
    BKObject();

    
    //void Translate(BKTransform transform_to, Space space);

};

#endif /* BKObject_hpp */