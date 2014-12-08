//
//  envBlock.cpp
//  FinalProject
//
//  Created by Simar Singh on 2014-12-07.
//  Copyright (c) 2014 Simarpreet Singh. All rights reserved.
//

#include "envBlock.h"

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

envBlock::envBlock(float l, float w, float h){
    length = l;
    height = h;
    width = w;
    translateZ = -100;
    
    rgb[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    rgb[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    rgb[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

void envBlock::addToTranslateZ(float i){
    translateZ+=i;
}

void envBlock::draw(){
    glPushMatrix();
    glColor3f(rgb[0], rgb[1], rgb[2]);
    glBegin(GL_QUADS);
        glVertex3d(length/2, 0, 0);
        glVertex3d(-1*length/2, 0, 0);
        glVertex3d(-1*length/2, 0, -1*width);
        glVertex3d(length/2, 0, -1*width);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3d(length/2, 0, 0);
        glVertex3d(length/2, height, 0);
        glVertex3d(length/2, height, -1*width);
        glVertex3d(length/2, 0, -1*width);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3d(-1*length/2, 0, 0);
        glVertex3d(-1*length/2, height, 0);
        glVertex3d(-1*length/2, height, -1*width);
        glVertex3d(-1*length/2, 0, -1*width);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3d(length/2, height, 0);
        glVertex3d(-1*length/2, height, 0);
        glVertex3d(-1*length/2, height, -1*width);
        glVertex3d(length/2, height, -1*width);
    glEnd();
    glPopMatrix();
}

bool envBlock::isExpired(float camZ){
    return (translateZ-width) > camZ;
}