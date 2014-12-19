//
//  game.h
//  FinalProject
//
//  Created by Simar Singh on 2014-12-07.
//  Copyright (c) 2014 Simarpreet Singh. All rights reserved.
//

#include <stdio.h>
#include <list>
#include "envBlock.h"
#include "particle.h"
#include "surface.h"

using namespace std;

class game{
public:
    float screenSizeX = 600;
    float screenSizeY = 600;
    
    float fpCamPos[3];
    float movingSpeed = 0.9;
    
    float envBlockSize[3];
    list<envBlock *> trainOfEnvBlocks;
    list<particle *> listOfParticles;
    
    game();
    
    void updateMethod();
    void draw();
    void setFPLook();
    
    void screenClick(int x, int y);
};