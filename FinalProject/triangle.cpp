//
//  triangle.cpp
//  FinalProject
//
//  Created by Simar Singh on 2014-12-19.
//  Copyright (c) 2014 Simarpreet Singh. All rights reserved.
//

#include "triangle.h"

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <iostream>

triangle::triangle(float l, float w){
    position[0] = RandomFloat(-10, 5);
    position[1] = 0.1;
    position[2] = RandomFloat(-15, -5);
    makeSurfaces();
}

void triangle::draw(){
    glPushMatrix();
    glColor3fv(rgb);
    glBegin(GL_QUADS);
    for(int i= 0; i<4; i++)
        glVertex3f(floor[i][0], floor[i][1], floor[i][2]);
    glEnd();
    glBegin(GL_TRIANGLES);
    for(int i= 0; i<3; i++)
        glVertex3f(side1[i][0], side1[i][1], side1[i][2]);
    glNormal3fv(crossProduct(side1[0], side1[1]));
    glEnd();
    glBegin(GL_TRIANGLES);
    for(int i= 0; i<3; i++)
        glVertex3f(side2[i][0], side2[i][1], side2[i][2]);
    glNormal3fv(crossProduct(side2[0], side2[1]));
    glEnd();
    glBegin(GL_TRIANGLES);
    for(int i= 0; i<3; i++)
        glVertex3f(side3[i][0], side3[i][1], side3[i][2]);
    glNormal3fv(crossProduct(side3[0], side3[1]));
    glEnd();
    glBegin(GL_TRIANGLES);
    for(int i= 0; i<3; i++)
        glVertex3f(side4[i][0], side4[i][1], side4[i][2]);
    glNormal3fv(crossProduct(side4[0], side4[1]));
    glEnd();
    glPopMatrix();
}

void triangle::makeSurfaces(){
    floor[0][0] = position[0];
    floor[0][1] = position[1];
    floor[0][2] = position[2];
    floor[1][0] = position[0]+length;
    floor[1][1] = position[1];
    floor[1][2] = position[2];
    floor[2][0] = position[0]+length;
    floor[2][1] = position[1];
    floor[2][2] = position[2]+length;
    floor[3][0] = position[0];
    floor[3][1] = position[1];
    floor[3][2] = position[2]+length;
//    listOfSurfaces.push_back(new surface(floor));
    
    float center[3] = {position[0]+(length/2), position[1]+5 ,position[2]+(length/2)};
    
    side1[0][0] = position[0];
    side1[0][1] = position[1];
    side1[0][2] = position[2];
    side1[1][0] = position[0]+length;
    side1[1][1] = position[1];
    side1[1][2] = position[2];
    side1[2][0] = center[0];
    side1[2][1] = center[1];
    side1[2][2] = center[2];
    listOfSurfaces.push_back(new surface(side1, 1));
    
    side2[0][0] = position[0]+length;
    side2[0][1] = position[1];
    side2[0][2] = position[2];
    side2[1][0] = position[0]+length;
    side2[1][1] = position[1];
    side2[1][2] = position[2]+length;
    side2[2][0] = center[0];
    side2[2][1] = center[1];
    side2[2][2] = center[2];
    listOfSurfaces.push_back(new surface(side2, 1));
    
    side3[0][0] = position[0]+length;
    side3[0][1] = position[1];
    side3[0][2] = position[2]+length;
    side3[1][0] = position[0];
    side3[1][1] = position[1];
    side3[1][2] = position[2]+length;
    side3[2][0] = center[0];
    side3[2][1] = center[1];
    side3[2][2] = center[2];
    listOfSurfaces.push_back(new surface(side3, 1));
    
    side4[0][0] = position[0];
    side4[0][1] = position[1];
    side4[0][2] = position[2]+length;
    side4[1][0] = position[0];
    side4[1][1] = position[1];
    side4[1][2] = position[2];
    side4[2][0] = center[0];
    side4[2][1] = center[1];
    side4[2][2] = center[2];
    listOfSurfaces.push_back(new surface(side4, 1));
}

float triangle::RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}


float * triangle::crossProduct(float v1[3], float v2[3]){
    float * n = new float[3];
    n[0] = v1[1]*v2[2] - v1[2]*v2[1];
    n[1] = v1[2]*v2[0] - v1[0]*v2[2];
    n[3] = v1[2]*v2[0] - v1[0]*v2[2];
    return n;
}

void triangle::triangleHit(){
    rgb[0] = 1;
    rgb[1] = 0;
    rgb[2] = 0;
}

float triangle::getZPosition(float translateZ){
    return position[2]+translateZ;
}
