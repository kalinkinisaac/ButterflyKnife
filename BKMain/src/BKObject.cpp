//
//  BKObject.cpp
//  ButterflyKnife
//
//  Created by Исаак Калинкин  on 12.02.16.
//  Copyright © 2016 BK. All rights reserved.
//

#include "include/BKObject.hpp"
BKObject::BKObject(){
	this->Transform = *new BKTransform;
}

BKObject::BKObject(BKTransform _Transform) {
	this->Transform = _Transform;
}



