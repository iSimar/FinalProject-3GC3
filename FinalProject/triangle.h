//
//  triangle.h
//  FinalProject
//
//  Created by Simar Singh on 2014-12-19.
//  Copyright (c) 2014 Simarpreet Singh. All rights reserved.
//

#ifndef __FinalProject__triangle__
#define __FinalProject__triangle__

#include <stdio.h>
#include <list>
#include "surface.h"

using namespace std;

class triangle{
public:
    float position[3];
    float length = 5;
    float rgb[3] = {0.7, 0.1, 0.7};
    float floor[4][3];
    float side1[3][3];
    float side2[3][3];
    float side3[3][3];
    float side4[3][3];
    
    triangle(float l, float w);
    void draw();
    void makeSurfaces();
    void triangleHit();
    float RandomFloat(float a, float b);
    
    float * crossProduct(float v1[3], float v2[3]);
    float getZPosition(float translateZ);
    
    
    
    list<surface *> listOfSurfaces;
    
};

#endif /* defined(__FinalProject__triangle__) */
