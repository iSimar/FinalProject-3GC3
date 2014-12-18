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

    obstacle1 = rand() % 3 - rand() % 10;
    obstacle2 = rand() % 5 + rand() % 10;
    size = rand() % 4 + 2;
    size2 = rand() % 4 + 2;
    
    rgb[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    rgb[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    rgb[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);


    setFloorWallsCeilingPoints();

}

void envBlock::addToTranslateZ(float i){
    translateZ+=i;
}

void envBlock::draw(){
    glPushMatrix();
    glColor3f(rgb[0], rgb[1], rgb[2]);
    glBegin(GL_QUADS);
        for(int i= 0; i<4; i++)
            glVertex3d(floor[i][0], floor[i][1], floor[i][2]);
    glEnd();
    glBegin(GL_QUADS);
        for(int i= 0; i<4; i++)
            glVertex3d(rightWall[i][0], rightWall[i][1], rightWall[i][2]);
    glEnd();
    glBegin(GL_QUADS);
    for(int i= 0; i<4; i++)
        glVertex3d(leftWall[i][0], leftWall[i][1], leftWall[i][2]);
    glEnd();
    glBegin(GL_QUADS);
    for(int i= 0; i<4; i++)
        glVertex3d(ceiling[i][0], ceiling[i][1], ceiling[i][2]);
    glEnd();
    glPopMatrix();

//Obstacles
    glEnable (GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1, 0, 0, 0.2);
    glBegin(GL_QUADS);
        glVertex3d(obstacle1,obstacle2,0);
        glVertex3d(obstacle1 + size2,obstacle2,0);
        glVertex3d(obstacle1 + size2,obstacle2 + size,0);
        glVertex3d(obstacle1,obstacle2 + size,0);
    glEnd();
}

bool envBlock::isExpired(float camZ){
    return (translateZ-width) > camZ;
}

void envBlock::setFloorWallsCeilingPoints(){
    floor[0][0] = length/2;
    floor[0][1] = 0;
    floor[0][2] = 0;
    floor[1][0] = -1*length/2;
    floor[1][1] = 0;
    floor[1][2] = 0;
    floor[2][0] = -1*length/2;
    floor[2][1] = 0;
    floor[2][2] = -1*width;
    floor[3][0] = length/2;
    floor[3][1] = 0;
    floor[3][2] = -1*width;
    
    listOfSurfaces.push_back(new surface(floor));
    
    rightWall[0][0] = length/2;
    rightWall[0][1] = 0;
    rightWall[0][2] = 0;
    rightWall[1][0] = length/2;
    rightWall[1][1] = height;
    rightWall[1][2] = 0;
    rightWall[2][0] = length/2;
    rightWall[2][1] = height;
    rightWall[2][2] = -1*width;
    rightWall[3][0] = length/2;
    rightWall[3][1] = 0;
    rightWall[3][2] = -1*width;
    
//    listOfSurfaces.push_back(new surface(rightWall));
    
    leftWall[0][0] = -1*length/2;
    leftWall[0][1] = 0;
    leftWall[0][2] = 0;
    leftWall[1][0] = -1*length/2;
    leftWall[1][1] = height;
    leftWall[1][2] = 0;
    leftWall[2][0] = -1*length/2;
    leftWall[2][1] = height;
    leftWall[2][2] = -1*width;
    leftWall[3][0] = -1*length/2;
    leftWall[3][1] = 0;
    leftWall[3][2] = -1*width;
    
//    listOfSurfaces.push_back(new surface(leftWall));
    
    ceiling[0][0] = length/2;
    ceiling[0][1] = height;
    ceiling[0][2] = 0;
    ceiling[1][0] = -1*length/2;
    ceiling[1][1] = height;
    ceiling[1][2] = 0;
    ceiling[2][0] = -1*length/2;
    ceiling[2][1] = height;
    ceiling[2][2] = -1*width;
    ceiling[3][0] = length/2;
    ceiling[3][1] = height;
    ceiling[3][2] = -1*width;
    
//    listOfSurfaces.push_back(new surface(ceiling));

}

void envBlock::checkCollisions(list<particle *> listOfParticles){
    for(list<particle *>::iterator i = listOfParticles.begin(); i != listOfParticles.end(); ++i){
        particle * currentParticle = *i;
        for(list<surface *>::iterator j = listOfSurfaces.begin(); j != listOfSurfaces.end(); ++j){
            surface * currentSurface = *j;
            float * temp = currentParticle->getPosition();
//            printf("temp: %f, %f, %f\n", temp[0], temp[1], temp[2]);
            if(currentSurface->isCoplanar(temp)){
                printf("gogogo");
                currentParticle->invertDirection(1);
            }
        }
    }
}