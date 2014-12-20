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

#include <iostream>


game::game(){
    fpCamPos[0] = 0;
    fpCamPos[1] = 10;
    fpCamPos[2] = 0;
    envBlockSize[0] = 20; //length
    envBlockSize[1] = 20; //width
    envBlockSize[2] = 20; //height
    trainOfEnvBlocks.push_back(new envBlock(envBlockSize[0], envBlockSize[1], envBlockSize[2]));
}

void game::updateMethod(){
    score+=10;
//    setScore(score);
    for(list<envBlock *>::iterator i = trainOfEnvBlocks.begin(); i != trainOfEnvBlocks.end(); ++i){
        envBlock * currentEnvBlock = *i;
        if(currentEnvBlock->isExpired(fpCamPos[2]))
            trainOfEnvBlocks.erase(i);
        else{
            currentEnvBlock->addToTranslateZ(movingSpeed);
            currentEnvBlock->checkCollisions(listOfParticles);
        }
        if(i==--trainOfEnvBlocks.end()){
            if(currentEnvBlock->translateZ>-100+currentEnvBlock->width)
                trainOfEnvBlocks.push_back(new envBlock(envBlockSize[0], envBlockSize[1], envBlockSize[2]));
        }
    }
    
    for(list<particle *>::iterator i = listOfParticles.begin(); i != listOfParticles.end(); ++i){
        particle * currentParticle = *i;
        if(currentParticle->isExpired(fpCamPos[2])){
            listOfParticles.erase(i);
        }
        else{
            currentParticle->move(0.5, 100, 1, movingSpeed);
        }
    }
    glassCameraCollision();
}

void game::draw(){
    for(list<envBlock *>::iterator i = trainOfEnvBlocks.begin(); i != trainOfEnvBlocks.end(); ++i){
        envBlock * currentEnvBlock = *i;
        glPushMatrix();
        glTranslatef(0, 0, currentEnvBlock->translateZ);
        currentEnvBlock->draw();
        glPopMatrix();
    }
    
    for(list<particle *>::iterator i = listOfParticles.begin(); i != listOfParticles.end(); ++i){
        particle * currentParticle = *i;
        currentParticle->renderParticle();
    }
    
}

void game::setFPLook(){
    gluLookAt(fpCamPos[0], fpCamPos[1], fpCamPos[2], fpCamPos[0],fpCamPos[1],fpCamPos[2]-1, 0,1,0);
}

void game::screenClick(int x, int y){
    numOfBalls-=1;
    if(numOfBalls==0){
        printf("GAMEOVERRRRR!!!");
    }
//    setBallsLeft(numOfBalls);
//    printf("%i %f\n",x,(screenSizeY - y));
    /* Converting x and y to world x and y
     */
    float x_world = -1*(((screenSizeX/2)-x)/screenSizeX)*((envBlockSize[0])/2);
    float y_world = (((screenSizeY/2)-y)/screenSizeY)*((envBlockSize[1])/2)+fpCamPos[1];
    

    listOfParticles.push_back(new particle(
                                           new point(fpCamPos[0], fpCamPos[1], fpCamPos[2]-10),
                                           new point(x_world*1.5, y_world-2, fpCamPos[2]-30),
                                           movingSpeed*0.04,
                                           1,
                                           300
                                           )
                              );
}

void game::glassCameraCollision(){
    envBlock * frontEnvBlock = trainOfEnvBlocks.front();
    for(list<glass *>::iterator i = frontEnvBlock->listOfGlasses.begin(); i != frontEnvBlock->listOfGlasses.end(); ++i){
        glass * currentGlass = *i;
        float glassZ = currentGlass->getZPosition(frontEnvBlock->translateZ);
        if(glassZ>0){
            if(currentGlass->vectors[1][0]<=0 && 0<=currentGlass->vectors[0][0]){
                if(currentGlass->vectors[0][1]<=10 && 10<=currentGlass->vectors[3][1]){
                    printf("GAMEOVERRRRR!!!");
            }
        }
            
    }
        
}
}



/*
 Code birunthaa has added
 drawtext conversion, from course website
 */
void game::drawStrokeText(char* text, int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glTranslatef(x, y, 0);
    glScalef(0.20, 0.20, 0.20);
    
    char* c;  //character iterator (ptr)
    for(c = text; *c != '\0'; c++) //stop when we hit null character
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *c); //print one char
    }
}
/*
 Code birunthaa has added
 set score when ball hits the walls
 */
string game:: setScore(){
    int score2 = score;
    //score+= 100;
    string finalScore = to_string(score2);
    return finalScore;
}
/*
 Code birunthaa has added
 balls left counter
 */
string game:: setBallsLeft(){
    int ballsLeft = numOfBalls;
    //ballsLeft-=1;
    
    string numBallsLeft = to_string(ballsLeft);
    return numBallsLeft;
}