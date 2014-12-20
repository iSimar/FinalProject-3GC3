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
//    translateZ=0;
    translateZ = -100;
    
//    rgb[0] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//    rgb[1] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//    rgb[2] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    
    rgb[0] = 0.122;
    rgb[1] = 0.745;
    rgb[2] = 0.631;
    setFloorWallsCeilingPoints();
    
    if(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)<0.2)
        listOfTriangles.push_back(new triangle(length, width));
    
    if(static_cast <float> (rand()) / static_cast <float> (RAND_MAX)<0.3)
        listOfGlasses.push_back(new glass());
    
//    for(list<glass *>::iterator i = listOfGlasses.begin(); i != listOfGlasses.end(); ++i){
//        glass * currentGlass = *i;
//        listOfSurfaces.merge(currentGlass->listOfSurfaces);
////        printf("adds");
//    }
    

}

void envBlock::addToTranslateZ(float i){
    translateZ+=i;
}

void envBlock::draw(){
    glPushMatrix();
    glColor3f(rgb[0]*0.5, rgb[1]*0.5, rgb[2]*0.5);
    glBegin(GL_QUADS);
    for(int i= 0; i<4; i++)
        glVertex3d(floor[i][0], floor[i][1], floor[i][2]);
    glNormal3fv(crossProduct(floor[0], floor[1]));
    glEnd();
    glBegin(GL_QUADS);
    //for(int i= 0; i<4; i++)
    glTexCoord2f(0, 0); glVertex3d(rightWall[0][0], rightWall[0][1], rightWall[0][2]);
    glTexCoord2f(0, 1); glVertex3d(rightWall[1][0], rightWall[1][1], rightWall[1][2]);
    glTexCoord2f(1, 1); glVertex3d(rightWall[2][0], rightWall[2][1], rightWall[2][2]);
    glTexCoord2f(1, 0); glVertex3d(rightWall[3][0], rightWall[3][1], rightWall[3][2]);
    glNormal3fv(crossProduct(rightWall[0], rightWall[1]));
    glEnd();
    glBegin(GL_QUADS);
    //for(int i= 0; i<4; i++)
    glTexCoord2f(0, 0); glVertex3d(leftWall[0][0], leftWall[0][1], leftWall[0][2]);
    glTexCoord2f(0, 1); glVertex3d(leftWall[1][0], leftWall[1][1], leftWall[1][2]);
    glTexCoord2f(1, 1); glVertex3d(leftWall[2][0], leftWall[2][1], leftWall[2][2]);
    glTexCoord2f(1, 0); glVertex3d(leftWall[3][0], leftWall[3][1], leftWall[3][2]);
    glNormal3fv(crossProduct(leftWall[0], leftWall[1]));
    glEnd();
    glColor3f(rgb[0], rgb[1], rgb[2]);
    glBegin(GL_QUADS);
    for(int i= 0; i<4; i++)
        glVertex3d(ceiling[i][0], ceiling[i][1], ceiling[i][2]);
    glNormal3fv(crossProduct(ceiling[0], ceiling[1]));
    glEnd();
    glPopMatrix();    
    
    for(list<triangle *>::iterator i = listOfTriangles.begin(); i != listOfTriangles.end(); ++i){
        triangle * currentTriangle = *i;
        currentTriangle->draw();
    }
    
    for(list<glass *>::iterator i = listOfGlasses.begin(); i != listOfGlasses.end(); ++i){
        glass * currentGlass = *i;
        currentGlass->draw();
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
    
    listOfSurfaces.push_back(new surface(rightWall));
    
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
    
    listOfSurfaces.push_back(new surface(leftWall));
    
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
    
    listOfSurfaces.push_back(new surface(ceiling));
}

void envBlock::checkCollisions(list<particle *> listOfParticles){
    for(list<particle *>::iterator i = listOfParticles.begin(); i != listOfParticles.end(); ++i){
        particle * currentParticle = *i;
        if(translateZ-width<=currentParticle->position->z && currentParticle->position->z<=translateZ){
            
            
            
            
            for(list<surface *>::iterator j = listOfSurfaces.begin(); j != listOfSurfaces.end(); ++j){
                float * particlePos = currentParticle->getPosition();
                surface * currentSurface = *j;
                float * intersection = currentSurface->getIntersection(particlePos, currentParticle->getDirection(), translateZ);
                if(intersection!=NULL){
                    float dist = currentSurface->distance(particlePos, intersection);
                    if(dist < 4)
                        if(currentSurface->pointInSurface(intersection, translateZ)){
                            currentParticle->reflectDirection(currentSurface->n);
                        }
                    
                }
            }
            
            
            
            for(list<triangle *>::iterator u = listOfTriangles.begin(); u != listOfTriangles.end(); ++u){
                triangle * currentTriangle = *u;
                for(list<surface *>::iterator h = currentTriangle->listOfSurfaces.begin(); h != currentTriangle->listOfSurfaces.end(); ++h){
                        surface * currentSurface = *h;
                        float * particlePos_1 = currentParticle->getPosition();
                        float * intersection_1 = currentSurface->getIntersection(particlePos_1, currentParticle->getDirection(), currentTriangle->getZPosition(translateZ));
                        if(intersection_1!=NULL){
                            float dist = currentSurface->distance(particlePos_1, intersection_1);
                            if(dist < 3){
                                if(currentSurface->pointInSurface(intersection_1, translateZ)){
//                                    printf("%f %f",  currentTriangle->getZPosition(translateZ) , currentSurface->points[0][2]);
                                    currentParticle->reflectDirection(currentSurface->n);
                                    currentTriangle->triangleHit();
                                }
                            }
                        
                        }
                }
                
            }
            
            for(list<glass *>::iterator b = listOfGlasses.begin(); b != listOfGlasses.end(); ++b){
                glass * currentGlass = *b;
                if(!currentGlass->mustDelete){
                float * particlePos_2 = currentParticle->getPosition();
                float glassZ = currentGlass->getZPosition(translateZ);
                if(glassZ-particlePos_2[2] >  -2){
                    if(currentGlass->vectors[1][0]<=particlePos_2[0] && particlePos_2[0]<=currentGlass->vectors[0][0]){                        if(currentGlass->vectors[0][1]<=particlePos_2[1] && particlePos_2[1]<=currentGlass->vectors[3][1]){
                            float * n = new float[3];
                            n[0] = 0; n[1] = 0; n[2] = 1;
                            currentParticle->reflectDirection(n);
                            currentGlass->mustDelete = 1;
                            listOfParticles.erase(i);
                        }
                    }
                    
                }
                }
                
            }
            
            
            
            
        }
    }
    
    for(list<glass *>::iterator b = listOfGlasses.begin(); b != listOfGlasses.end(); ++b){
        glass * currentGlass = *b;
        if(currentGlass->mustDelete){
            listOfGlasses.erase(b);
        }
    }
}

float * envBlock::crossProduct(float v1[3], float v2[3]){
    float * n = new float[3];
    n[0] = v1[1]*v2[2] - v1[2]*v2[1];
    n[1] = v1[2]*v2[0] - v1[0]*v2[2];
    n[3] = v1[2]*v2[0] - v1[0]*v2[2];
    return n;
}