//
//  envBlock.h
//  FinalProject
//
//  Created by Simar Singh on 2014-12-07.
//  Copyright (c) 2014 Simarpreet Singh. All rights reserved.
//

#include <stdio.h>
#include <list>
#include "particle.h"
#include "surface.h"

using namespace std;

class envBlock{
public:
    float length;
    float width;
    float height;
    
    float rgb[3];
    
    float translateZ;
    
    float floor[4][3];
    float rightWall[4][3];
    float leftWall[4][3];
    float ceiling[4][3];

    float randX;
    float randZ;
    float randomBlock;

    //float leftDoor;
    //float rightDoor;
    
    list<surface *> listOfSurfaces;
    
    envBlock(float l, float w, float h);
    //envBlock(float l, float w, float h, int t);
    
    void addToTranslateZ(float i);
    
    void draw();
    
    bool isExpired(float camZ);
    
    void setFloorWallsCeilingPoints();
    
    list<surface *> getSurfaces();
    
    void checkCollisions(list<particle *> listOfParticles);
    
};