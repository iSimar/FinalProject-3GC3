//
//  surface.cpp
//  FinalProject
//
//  Created by Simar Singh on 2014-12-14.
//  Copyright (c) 2014 Simarpreet Singh. All rights reserved.
//

#include "surface.h"

surface::surface(float pointsArray[3][3], bool triangleBool){
    isTriangle = triangleBool;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            points[i][j] = pointsArray[i][j];
    
    for(int i=0; i<3; i++)
        originalZPoints[i] = points[i][2];
    
    float * v1 = new float[3];
    v1[0] = points[0][0]-points[1][0];
    v1[1] = points[0][1]-points[1][1];
    v1[2] = points[0][2]-points[1][2];
    
    
    float * v2 = new float[3];
    v2[0] = points[2][0]-points[1][0];
    v2[1] = points[2][1]-points[1][1];
    v2[2] = points[2][2]-points[1][2];
    
    n = crossProduct(v1, v2);
    float n_b = sqrtf(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);
    n[0]*=1/n_b;
    n[1]*=1/n_b;
    n[2]*=1/n_b;
    
    
    planeEquationX = n[0];
    planeEquationY = n[1];
    planeEquationZ = n[2];
    planeEquationD = -1*(n[0]*points[0][0] + n[1]*points[0][1] + n[2]*points[0][2]);
}

surface::surface(float pointsArray[4][3]){
    for(int i=0; i<4; i++)
        for(int j=0; j<3; j++)
            points[i][j] = pointsArray[i][j];
    
    for(int i=0; i<4; i++)
        originalZPoints[i] = points[i][2];
    
    float * v1 = new float[3];
    v1[0] = points[0][0]-points[1][0];
    v1[1] = points[0][1]-points[1][1];
    v1[2] = points[0][2]-points[1][2];
    
    
    float * v2 = new float[3];
    v2[0] = points[2][0]-points[1][0];
    v2[1] = points[2][1]-points[1][1];
    v2[2] = points[2][2]-points[1][2];
    
    n = crossProduct(v1, v2);
    float n_b = sqrtf(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);
    n[0]*=1/n_b;
    n[1]*=1/n_b;
    n[2]*=1/n_b;
    
    
    planeEquationX = n[0];
    planeEquationY = n[1];
    planeEquationZ = n[2];
    planeEquationD = -1*(n[0]*points[0][0] + n[1]*points[0][1] + n[2]*points[0][2]);
//        printf("p1: %f %f %f\n", points[0][0], points[0][1], points[0][2]);
//        printf("p2: %f %f %f\n", points[1][0], points[1][1], points[1][2]);
//        printf("p3: %f %f %f\n", points[2][0], points[2][1], points[2][2]);
//        printf("p4: %f %f %f\n", points[3][0], points[3][1], points[3][2]);
//        printf("normal: %f %f %f\n", n[0], n[1], n[2]);
//        printf("%f, %f, %f, %f\n", planeEquationX, planeEquationY, planeEquationZ, planeEquationD);
}

void surface::updatePoints(float newZ){
    float diff = points[2][2] - points[0][2];
    points[0][2] = newZ;
    points[1][2] = newZ;
    points[2][2] = newZ+diff;
    points[3][2] = newZ+diff;
    
    
//    
//    printf("p1: %f %f %f\n", points[0][0], points[0][1], points[0][2]);
//    printf("p2: %f %f %f\n", points[1][0], points[1][1], points[1][2]);
//    printf("p3: %f %f %f\n", points[2][0], points[2][1], points[2][2]);
//    printf("p4: %f %f %f\n", points[3][0], points[3][1], points[3][2]);
    float * v1 = new float[3];
    v1[0] = points[0][0]-points[1][0];
    v1[1] = points[0][1]-points[1][1];
    v1[2] = points[0][2]-points[1][2];
//    printf("v1: %f %f %f\n", v1[0], v1[1], v1[2]);
    
    float * v2 = new float[3];
    v2[0] = points[2][0]-points[1][0];
    v2[1] = points[2][1]-points[1][1];
    v2[2] = points[2][2]-points[1][2];
//    printf("v2: %f %f %f\n", v2[0], v2[1], v2[2]);
    
    n = crossProduct(v1, v2);
    float n_b = sqrtf(n[0]*n[0]+n[1]*n[1]+n[2]*n[2]);
    n[0]*=1/n_b;
    n[1]*=1/n_b;
    n[2]*=1/n_b;
    
    
    planeEquationX = n[0];
    planeEquationY = n[1];
    planeEquationZ = n[2];
    planeEquationD = -1*(n[0]*points[0][0] + n[1]*points[0][1] + n[2]*points[0][2]);
//    printf("normal: %f %f %f\n", n[0], n[1], n[2]);
//    printf("%f, %f, %f, %f\n", planeEquationX, planeEquationY, planeEquationZ, planeEquationD);

}

float * surface::getIntersection(float origin[3], float direction[3], float newZ){
    updatePoints(newZ);
//    printf("* %f\n", points[0][2]);
    float top = -1*(planeEquationX*origin[0] + planeEquationY*origin[1] + planeEquationZ*origin[2] + planeEquationD);
    float bottom = planeEquationX*direction[0] + planeEquationY*direction[1] + planeEquationZ*direction[2];
    if(bottom!=0){
        float result = top/bottom;
        if(result>0){
            float * rtn = new float[3];
            rtn[0] = origin[0] + direction[0]*result;
            rtn[1] = origin[1] + direction[1]*result;
            rtn[2] = origin[2] + direction[2]*result;
            return rtn;
        }
        return NULL;
    }
    return NULL;
}

bool surface::pointInSurface(float point[3], float translateZ){
//    updatePoints(translateZ);
//    printf("%i %i %i\n", sameSide(point, points[0], points[1], points[2]),
//           sameSide(point, points[1], points[0], points[2]),
//           sameSide(point, points[2], points[0], points[1]));
    if(sameSide(point, points[0], points[1], points[2]) &&
       sameSide(point, points[1], points[0], points[2]) &&
       sameSide(point, points[2], points[0], points[1])){
        return 1;
    }
    else{
        if(isTriangle){
//            printf("*****");
            return 0;
        }
        if(sameSide(point, points[2], points[3], points[0]) &&
           sameSide(point, points[3], points[2], points[0]) &&
           sameSide(point, points[0], points[2], points[3])){
            return 1;
//            printf("asdssd");
        }
        else{
//            printf("asdssd");
            return 0;
        }
    }
    return 0;
}

//---Utility Functions:
float surface::dotProduct(float v1[3], float v2[3]){
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

float * surface::crossProduct(float v1[3], float v2[3]){
    float * n = new float[3];
    n[0] = v1[1]*v2[2] - v1[2]*v2[1];
    n[1] = v1[2]*v2[0] - v1[0]*v2[2];
    n[2] = v1[0]*v2[1] - v1[1]*v2[0];
    return n;
}

float * surface::subtract(float v2[3], float v1[3]){
    float * v1v2 = new float[3];
    v1v2[0] = v2[0] - v1[0];
    v1v2[1] = v2[1] - v1[1];
    v1v2[2] = v2[2] - v1[2];
    return v1v2;
}

float surface::distance(float v1[3], float v2[3]){
    float * sub = subtract(v2, v1);
    return sqrtf(dotProduct(sub, sub));
}

bool surface::sameSide(float p1[3], float p2[3], float a[3], float b[3]){
    float * cp1 = crossProduct(subtract(b, a), subtract(p1, a));
    float * cp2 = crossProduct(subtract(b, a), subtract(p2, a));
    if(dotProduct(cp1, cp2) >= 0)
        return 1;
    else
        return 0;
}