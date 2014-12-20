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
#include <math.h>
//#include "triangle.h"

class surface{
public:
    float objectID;
    float points[4][3];
    
    bool isTriangle = 0;
    
    float originalZPoints[4];
    
    float * n = new float[3];
    
    float planeEquationX;
    float planeEquationY;
    float planeEquationZ;
    float planeEquationD;
    
    surface(float pointsArray[3][3], bool boolTriangle);
    
    surface(float pointsArray[4][3]);
    
    void updatePoints(float translateZ);
    
    float * getIntersection(float origin[3], float direction[3], float translateZ);
    bool pointInSurface(float point[3], float translateZ);
    
    //---Utility Functions:
    float dotProduct(float v1[3], float v2[3]);
    float * crossProduct(float v1[3], float v2[3]);
    float * subtract(float v2[3], float v1[3]);
    float distance(float v1[3], float v2[3]);
    bool sameSide(float p1[3], float p2[3], float a[3], float b[3]);
    
};

#endif /* defined(__FinalProject__surface__) */
