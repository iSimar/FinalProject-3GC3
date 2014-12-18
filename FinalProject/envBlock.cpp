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

    randX = rand() % 20 - 10;
    randZ = rand() % 20 - 10;
    
    rgb[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    rgb[1] = rgb[0];
    rgb[2] = rgb[0];
    //rgb[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    //rgb[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    
    setFloorWallsCeilingPoints();

}

/*
envBlock::envBlock(float l, float w, float h, int t){
    length = 1;
    height = h;
    width = w; 
    translateZ = -100;

    TYPE = t;

    rgb[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    rgb[1] = rgb[0];
    rgb[2] = rgb[0];

    setFloorWallsCeilingPoints();

}
*/

void envBlock::addToTranslateZ(float i){
    translateZ+=i;
}

void envBlock::draw(int t){
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

    if(t == 1){
        glColor3f(1, 0, 0);
        glBegin(GL_TRIANGLES);
            glVertex3d(randX-2,0,randZ);
            glVertex3d(randX+2,0,randZ);
            glVertex3d(randX,0,randZ+2);
        glEnd();
        glColor3f(1, 1, 0);
        glBegin(GL_TRIANGLES);
            glVertex3d(randX-2,0,randZ);
            glVertex3d(randX,0,randZ+2);
            glVertex3d(randX,2,randZ+1);
        glEnd();
        glColor3f(0, 1, 0);
        glBegin(GL_TRIANGLES);
            glVertex3d(randX+2,0,randZ);
            glVertex3d(randX,0,randZ+2);
            glVertex3d(randX,2,randZ+1);
        glEnd();
        /*
        glColor3f(0, 0, 1);
        glBegin(GL_TRIANGLES);
            glVertex3d(randX+2,0,randZ+2);
            glVertex3d(randX-2,0,randZ+2);
            glVertex3d(randX,2,randZ+2);
        glEnd();
        */
    }
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