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
    
    bool isGameOver = 0;
    
    int numOfBalls = 8;
    int score = 0;
    
    float fpCamPos[3];
    float movingSpeed = 0.7;
    
    float envBlockSize[3];
    list<envBlock *> trainOfEnvBlocks;
    list<particle *> listOfParticles;
    
    void glassCameraCollision();
    
    game();
    
    void updateMethod();
    void draw();
    void setFPLook();
    
    void screenClick(int x, int y);
    
    void drawStrokeText(char* text, int x, int y);
    string setScore();
    string setBallsLeft();
};