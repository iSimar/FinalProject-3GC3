//
//  glass.cpp
//  FinalProject
//
//  Created by Simar Singh on 2014-12-20.
//  Copyright (c) 2014 Simarpreet Singh. All rights reserved.
//

#include "glass.h"

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

glass::glass(){
    position[0] = randomFloat(-10,10);
    position[1] = randomFloat(0,20);
    position[2] = randomFloat(0,15);
//    position[0] = 0;
//    position[1] = 3;
//    position[2] = 0;
    width = randomFloat(10, 20);
    height = randomFloat(10, 20);
//    printf("%f %f %f\n", position[0], position[1], position[2]);
    makeSurfaces();
}

float glass::randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void glass::draw(){
    glPushMatrix();
    glColor4fv(rgba);
    glBegin(GL_QUADS);
    for(int i= 0; i<4; i++){
        glVertex2fv(vectors[i]);
//        glVertex3f(vectors[i][0], vectors[i][1], vectors[i][2]);
    }
    glNormal3f(0, 0, 1);
    glEnd();
    glPopMatrix();
}

void glass::makeSurfaces(){
    vectors[0][0]=position[0];
    vectors[0][1]=position[1];
    vectors[0][2]=position[2];
    vectors[1][0]=position[0]-width;
    vectors[1][1]=position[1];
    vectors[1][2]=position[2];
    vectors[2][0]=position[0]-width;
    vectors[2][1]=position[1]+height;
    vectors[2][2]=position[2];
    vectors[3][0]=position[0];
    vectors[3][1]=position[1]+height;
    vectors[3][2]=position[2];
    
    listOfSurfaces.push_back(new surface(vectors));
}

float glass::getZPosition(float translateZ){
    return vectors[0][2]+translateZ;
}

void glass::glassHit(){
    
}