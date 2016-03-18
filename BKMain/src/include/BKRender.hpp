//
//  BKRender.hpp
//  BKS
//
//  Created by Исаак Калинкин  on 18.03.16.
//  Copyright © 2016 BK. All rights reserved.
//

#ifndef BKRender_hpp
#define BKRender_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "BKObject.hpp"
#include "BKCamera.hpp"

using namespace std;
const int MAX_L = 64; //max count of layers

class Layer
{
private:
    vector<BKObject> objects;
public:
    void AddObject(BKObject object);
    void DeleteObject(BKObject object);
    void Clear();
};
class Map
{
    
};
class Scene
{
private:
    int max_layer_flag, min_layer_flag;
    Map map;
    Layer layers[MAX_L];
public:
    Scene();
    void SetMap(Map map);
    void AddLayer();
    void PutObject(BKObject object);
    void AddObject(BKObject object, int id);
    void PushObject(BKObject object);
    
};
class Render
{
    Scene scene;
    BKCamera* camera;
    //double fps;
    void Draw(sf::RenderWindow window);
};




#endif /* BKRender_hpp */
