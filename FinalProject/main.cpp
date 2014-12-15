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

#ifdef _WIN32
#   include <windows.h>
#endif

#include <iostream>
#include "game.h"

//mode on or off constants
const int OFF = 0;
const int ON = 1;

int firstPersonMode = ON;

float camPos[] = {50, 50, 50};

float lightpos[] = {-10, 20, -20, 1.0};
float lightpos1[] = {10, 20, -20, 1.0};
float lightpos2[] = {-10, 0, -20, 1.0};
float lightpos3[] = {10, 0, -20, 1.0};
float lightDir[] = {0, 0 ,1};

game * mainGame = new game();

void display(){
    //setup of material values for light
    float m_amb[] = {0.23, 0.22, 0.23, 1.0};
    float m_dif[] = {0.2, 0.2, 0.2, 1.0};
    float m_spec[] = {0.10, 0.1, 0.1, 1.0};
    float shiny = 27;
    
//    enable material
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glColorMaterial(GL_AMBIENT, GL_DIFFUSE);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if(firstPersonMode==OFF)
        gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
    else
        mainGame->setFPLook();
    
    mainGame->drawEnvBlocks();
    
    glutSwapBuffers();
    
}

void updateMethod(int value){
    mainGame->updateMethod();
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
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluPerspective(45, 1, 1, 100);
            }
            else{
                firstPersonMode = OFF;
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluPerspective(450, 1, 1, 1000);
            }
            break;
        case 'n':
            camPos[1] += 2;
            break;
            
        case 'm':
            camPos[1] -= 2;
            break;
    }
    glutPostRedisplay();
}

void init(void){
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_COLOR_MATERIAL);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir);
    glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);
    glLightfv(GL_LIGHT2, GL_POSITION, lightpos2);
    glLightfv(GL_LIGHT3, GL_POSITION, lightpos3);
    
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

//    glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    init();
    glutMainLoop();
    return 0;
}

