//
//  game.cpp
//  FinalProject
//
//  Created by Simar Singh on 2014-12-07.
//  Copyright (c) 2014 Simarpreet Singh. All rights reserved.
//

#include "game.h"

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#ifdef _WIN32
#   include <windows.h>
#endif

#include <iostream>

game::game(){
    trainOfEnvBlocks.push_back(new envBlock(20, 20, 20));
}

void game::updateMethod(){
    for(list<envBlock *>::iterator i = trainOfEnvBlocks.begin(); i != trainOfEnvBlocks.end(); ++i){
        envBlock * currentEnvBlock = *i;
        if(currentEnvBlock->isExpired(fpCamPos[2]))
            trainOfEnvBlocks.erase(i);
        else
            currentEnvBlock->addToTranslateZ(movingSpeed);
        
        if(i==--trainOfEnvBlocks.end()){
//            printf("%f\n", currentEnvBlock->translateZ);
            if(currentEnvBlock->translateZ>-100+currentEnvBlock->width)
                trainOfEnvBlocks.push_back(new envBlock(20, 20, 20));
        }
    }
}

void game::drawEnvBlocks(){
    for(list<envBlock *>::iterator i = trainOfEnvBlocks.begin(); i != trainOfEnvBlocks.end(); ++i){
        envBlock * currentEnvBlock = *i;
        glPushMatrix();
        glTranslatef(0, 0, currentEnvBlock->translateZ);
        currentEnvBlock->draw();
        glPopMatrix();
    }
}

void game::setFPLook(){
    gluLookAt(0, 10, 0, 0,10,-1, 0,1,0);
}