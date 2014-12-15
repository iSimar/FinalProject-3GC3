//
//  surface.h
//  FinalProject
//
//  Created by Simar Singh on 2014-12-14.
//  Copyright (c) 2014 Simarpreet Singh. All rights reserved.
//

#ifndef __FinalProject__surface__
#define __FinalProject__surface__

#include <stdio.h>
#include <list>

class surface{
public:
    float objectID;
    float points[4][3];
    float planeEquationX;
    float planeEquationY;
    float planeEquationZ;
    float planeEquationD;
    surface(float pointsArray[4][3]);
    bool isCoplanar(float point[3]);
};

#endif /* defined(__FinalProject__surface__) */
