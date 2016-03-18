//
//  BKObject.hpp
//  ButterflyKnife
//
//  Created by Исаак Калинкин  on 12.02.16.
//  Copyright © 2016 BK. All rights reserved.
//

#ifndef BKObject_hpp
#define BKObject_hpp
#include <SFML/Graphics.hpp>
#include "BKTransform.hpp"
//#include "BKRender.hpp"
class Mesh{
    sf::Texture texture;
};

class BKObject{
private:
public:
    BKTransform Transform;
    BKObject();
    BKObject(BKTransform _Transform);
};

#endif /* BKObject_hpp */
