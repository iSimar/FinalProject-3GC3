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

envBlock::envBlock(){
    length = 10;
    height = 10;
    width = 10;
    
    translateZ = -100-(width/2);
}

envBlock::envBlock(float l, float w, float h){
    length = l;
    height = w;
    width = h;
    
    translateZ = -100-(width/2);
}

void envBlock::addToTranslateZ(float i){
    translateZ+=i;
}

void envBlock::draw(){
    glPushMatrix();
    glBegin(GL_QUADS);
        glVertex3d(length/2, 0, width/2);
        glVertex3d(-1*length/2, 0, width/2);
        glVertex3d(-1*length/2, 0, -1*width/2);
        glVertex3d(length/2, 0, -1*width/2);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3d(length/2, 0, width/2);
        glVertex3d(length/2, height, width/2);
        glVertex3d(length/2, height, -1*width/2);
        glVertex3d(length/2, 0, -1*width/2);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3d(-1*length/2, 0, width/2);
        glVertex3d(-1*length/2, height, width/2);
        glVertex3d(-1*length/2, height, -1*width/2);
        glVertex3d(-1*length/2, 0, -1*width/2);
    glEnd();
    glBegin(GL_QUADS);
        glVertex3d(length/2, height, width/2);
        glVertex3d(-1*length/2, height, width/2);
        glVertex3d(-1*length/2, height, -1*width/2);
        glVertex3d(length/2, height, -1*width/2);
    glEnd();
    glPopMatrix();
}