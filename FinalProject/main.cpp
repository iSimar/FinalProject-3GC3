/*
 * Final Project - 3GC3 
 * Team Members:
 * - Simarpreet Singh (1216728)
 */

#include <stdio.h>
#include <stdlib.h>

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

#include "envBlock.h"

//mode on or off constants
const int OFF = 0;
const int ON = 1;

int firstPersonMode = ON;

float camPos[] = {20, 20, 20};

float speed = 0.5;

envBlock * testBlock = new envBlock(20,20,20);


void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(firstPersonMode==OFF)
        gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
    else
        gluLookAt(0, 10, 0, 0,10,-1, 0,1,0);
//    glutSolidSphere(2, 16, 16);
    glTranslatef(0, 0, testBlock->translateZ);
    testBlock->draw();
    glutSwapBuffers();
    
}

void updateMethod(int value){
    testBlock->addToTranslateZ(speed);
    glutTimerFunc(16, updateMethod, 0);
    glutPostRedisplay();
}

void special(int key, int x, int y){
    /* arrow key presses move the camera */
    switch(key)
    {
        case GLUT_KEY_LEFT:
            camPos[0]-=2;
            break;
            
        case GLUT_KEY_RIGHT:
            camPos[0]+=2;
            break;
            
        case GLUT_KEY_UP:
            camPos[2] -= 2;
            break;
            
        case GLUT_KEY_DOWN:
            camPos[2] += 2;
            break;
            
        case GLUT_KEY_HOME:
            camPos[1] += 2;
            break;
            
        case GLUT_KEY_END:
            camPos[1] -= 2;
            break;
            
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    switch (key){
        case 'q':
            exit(0);
            break;
        case 'f':
            if (firstPersonMode == OFF){
                firstPersonMode = ON;
            }
            else{
                firstPersonMode = OFF;
            }
            break;
    }
    glutPostRedisplay();
}

void init(void){
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45, 1, 1, 100);
}

int main(int argc, char ** argv){
    glutInit(&argc, argv);		//starts up GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Final Project");	//creates the window
    
    glutDisplayFunc(display);	//registers "display" as the display callback function
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    
    glutTimerFunc(16, updateMethod, 0);
    
    glEnable(GL_DEPTH_TEST);
    init();
    glutMainLoop();
    return 0;
}

