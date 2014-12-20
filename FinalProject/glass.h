//
//  glass.h
//  FinalProject
//
//  Created by Simar Singh on 2014-12-20.
//  Copyright (c) 2014 Simarpreet Singh. All rights reserved.
//

#ifndef __FinalProject__glass__
#define __FinalProject__glass__

#include <stdio.h>
#include <list>
#include "surface.h"

using namespace std;

class glass{
public:
    float position[3];
    glass();
    float width;
    float height;
    void draw();
    float vectors[4][3];
    
    bool mustDelete = 0;
    
    float rgb[3] = {0.2, 0.1, 0.7};
    
    float randomFloat(float a, float b);
    void makeSurfaces();
    list<surface *> listOfSurfaces;
    float getZPosition(float translateZ);
    void glassHit();
};

#endif /* defined(__FinalProject__glass__) */
