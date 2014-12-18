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

    //Variables for obstacle positioning
    float obstacle1;
    float obstacle2;
    float size;
    float size2;

    
    list<surface *> listOfSurfaces;
    
    envBlock(float l, float w, float h);
    
    void addToTranslateZ(float i);
    
    void draw();
    
    bool isExpired(float camZ);
    
    void setFloorWallsCeilingPoints();
    
    list<surface *> getSurfaces();
    
    void checkCollisions(list<particle *> listOfParticles);
    
};