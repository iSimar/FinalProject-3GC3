//
//  surface.cpp
//  FinalProject
//
//  Created by Simar Singh on 2014-12-14.
//  Copyright (c) 2014 Simarpreet Singh. All rights reserved.
//

#include "surface.h"

surface::surface(float pointsArray[4][3]){
    for(int i=0; i<4; i++)
        for(int j=0; j<3; j++)
            points[i][j] = pointsArray[i][j];

    float v1[3] = {points[0][0]-points[1][0], points[0][1]-points[1][1], points[0][2]-points[1][2]};
    float v2[3] = {points[2][0]-points[1][0], points[2][1]-points[1][1], points[2][2]-points[1][2]};
    float n[3] = {v1[1]*v2[2] - v1[2]*v2[1], v1[2]*v2[0] - v1[0]*v2[2], v1[0]*v2[1] - v1[1]*v2[0]};
    planeEquationX = n[0];
    planeEquationY = n[1];
    planeEquationZ = n[2];
    planeEquationD = -1*(n[0]*points[0][0] + n[1]*points[0][1] + n[2]*points[0][2]);
//    printf("v1: %f, %f, %f\n", v1[0], v1[1], v1[2]);
//    printf("v2: %f, %f, %f\n", v2[0], v2[1], v2[2]);
//    printf("n: %f, %f, %f\n", n[0], n[1], n[2]);
//    printf("X: %f Y: %f, Z: %f, D: %f\n", planeEquationX, planeEquationY, planeEquationZ, planeEquationD);
}

bool surface::isCoplanar(float point[3]){
    float result = planeEquationX*point[0] + planeEquationY*(point[1]-1) + planeEquationZ*point[2];
    //printf("%f\n", result);
    return result < 0;
}