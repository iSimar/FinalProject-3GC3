//
//  particle.cpp
//  Assignment 2
//
//  Created by Simarpreet Singh on 2014-11-02.
//  Copyright (c) 2014 Simarpreet Singh. All rights reserved.
//

#include <stdlib.h>
#include "point.h"
#include "particle.h"

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


particle::particle(point * position_, float size_){
    position = position_;
    size = size_;
    rgb_color = new int[3];
    rgb_color[0] = 255;
    rgb_color[1] = 0;
    rgb_color[2] = 0;
    rotation = new int[3];
    rotation[0] = 0;
    rotation[1] = 0;
    rotation[2] = 0;
}

particle::particle(point * position_, point * direction_, float size_, float lifespan_){
    position = position_;
    direction = direction_;
    speed = 0.02;
    rotation = generateRandomRotationAngles();
    size = size_;
    rgb_color = generateRandomRGB();
    lifespan = lifespan_;
}

particle::particle(point * position_, point * direction_, float speed_,  float size_, float lifespan_){
    position = position_;
    direction = direction_;
    speed = speed_;
    rotation = generateRandomRotationAngles();
    size = size_;
    rgb_color = generateRandomRGB();
    lifespan = lifespan_;
}

particle::particle(point * position_, point * direction_, float speed_, float size_, float lifespan_, int * color_){
    position = position_;
    direction = direction_;
    speed = speed_;
    rotation = generateRandomRotationAngles();
    size = size_;
    rgb_color = color_;
    lifespan = lifespan_;
}


int * particle::generateRandomRGB(){
    int * rgb_color = new int[3];
    rgb_color[0] = (int)(rand()%255);
    rgb_color[1] = (int)(rand()%255);
    rgb_color[2] = (int)(rand()%255);
    return rgb_color;
}

int * particle::generateRandomRotationAngles(){
    int * rotationAngles = new int[3];
    rotationAngles[0] = (int)(rand()%360);
    rotationAngles[1] = (int)(rand()%360);
    rotationAngles[2] = (int)(rand()%360);
    return rotationAngles;
}

float * particle::getPosition(){
    float * positionArr = new float[3];
    positionArr[0] = position->x;
    positionArr[1] = position->y;
    positionArr[2] = position->z;
    return positionArr;
}

float * particle::getDirection(){
    float * directionArr = new float[3];
    directionArr[0] = direction->x;
    directionArr[1] = direction->y;
    directionArr[2] = direction->z;
    return directionArr;
}

int * particle::getRGBColor(){
    return rgb_color;
}

int * particle::getRotationAngles(){
    return rotation;
}

float particle::getSize(){ return size; }


void particle::move(float gravity, float floorSize, int friction, float envMovingSpeed){
    
//    if(isTouchingFloor(floorSize)){
//        invertDirection(friction);
//    }
    
    position->x += direction->x * speed;
    position->y += direction->y  * speed;
    position->z += direction->z * speed;
    
    direction->y -= gravity;
    
    incrementAge();
    
    rotation[0]+=1;
    rotation[1]+=1;
    rotation[2]+=1;
    
    if(withTheTrain){
        translateZ+= envMovingSpeed;
        speed*=1.003;
    }
    
}

void particle::incrementAge(){ age++; }

bool particle::isExpired(){
    return age>lifespan;
}

bool particle::isExpired(float camPosZ){
    if(position->y < -2)
        return 1;
    if(age>lifespan){
        return 1;
    }
    float * temp = getPosition();
    float realZPos =  translateZ + temp[2];
//    printf("%f\n", realZPos);
    return realZPos > camPosZ;
}

bool particle::isTouchingFloor(float floorSize){
    if(position->x<=floorSize && position->x>=-1*floorSize){
        if(position->z<=floorSize && position->z>=-1*floorSize){
            if(position->y<=size){
                return 1;
            }
        }
    }
    return 0;
}

void particle::invertDirection(int friction){
    withTheTrain = 1;
    direction->y*=-1;
    if(friction==1){
        speed*=0.50;
    }
    position->y+=1;
}

void particle::renderParticle(){
    glPushMatrix(); // push back the matrix
    float * pPosition = getPosition(); // get particle position array
    int * pRGBColor = getRGBColor(); // get particle color array
    int * pRotationAngles = getRotationAngles(); // get particle rotation angle array
    float pSize = getSize(); // get particle size
    glTranslatef(pPosition[0], pPosition[1], pPosition[2]+translateZ); //translate to the corrdinates of particle position
    glColor3b(pRGBColor[0], pRGBColor[1], pRGBColor[2]); // set the color to particle color
    glRotatef(pRotationAngles[0], 1, 0, 0); //rotation angle in x axis
    glRotatef(pRotationAngles[1], 0, 1, 0); //rotation angle in y axis
    glRotatef(pRotationAngles[2], 0, 0, 1); //rotation angle in z axis
    glutSolidSphere(pSize, 16, 16); //draw a solid sphere with radius as the particle size
    glPopMatrix(); // pop the matrix
}

void particle::reflectDirection(float normal[3]){
    float * dir = getDirection();
    float dot = normal[0]*dir[0] + normal[1]*dir[1] + normal[2]*dir[2];
    direction->x = -2*dot*normal[0] + direction->x;
    direction->y = -2*dot*normal[1] + direction->y;
    direction->z = -2*dot*normal[2] + direction->z;
    speed*=0.50;
    withTheTrain = 1;
}
