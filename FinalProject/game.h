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

using namespace std;

class game{
public:
    float fpCamPos[3];
    float movingSpeed = 1;
    list<envBlock *> trainOfEnvBlocks;
    
    game();
    
    void updateMethod();
    void drawEnvBlocks();
    void setFPLook();
};