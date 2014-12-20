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

#include "game.h"

//mode on or off constants
const int OFF = 0;
const int ON = 1;

int firstPersonMode = ON;

float camPos[] = {50, 50, 50};

//float lightpos1[] = {-10, 20, -60, 1.0};
//float lightpos1[] = {0, 10, 20, 1.0};
float lightpos[] = {0, -10, 53, 1.0};
float lightpos1[] = {-130, -10, 79, 1.0};
float lightpos2[] = {0, -10, 79, 1.0};
float lightDir[] = {0, 1 ,-1};
//float lightDir[] = {0,  ,0};
float lightDif[] = {1, 1, 1, 1};
float lightSpec[] = {1, 1, 1, 1 };

game * mainGame = new game();

void display(){
    //setup of material values for light
    float m_amb[] = {0.23, 0.22, 0.23, 1.0};
    float m_dif[] = {0.9, 0.9, 0.9, 1.0};
    float m_spec[] = {0.1, 0.1, 0.1, 1.0};
    float shiny = 1;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
    glColorMaterial(GL_AMBIENT, GL_DIFFUSE);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if(firstPersonMode==OFF)
        gluLookAt(camPos[0], camPos[1], camPos[2], 0,10,0, 0,1,0);
    else
        mainGame->setFPLook();
    
    /*
     Code birunthaa has added
     drawtext for both score and balls left
     */
    mainGame->draw();
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    mainGame->drawStrokeText((char*)"Score:", 400, 555);
    char* score = (char*)mainGame->setScore().c_str();
    mainGame->drawStrokeText(score, 500, 555);
    mainGame->drawStrokeText((char*)"Balls Left:", 400, 525);
    char* ballLeft = (char*)mainGame->setBallsLeft().c_str();
    mainGame->drawStrokeText(ballLeft, 550, 525);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    
    
    
    glutSwapBuffers();
    
}

void updateMethod(int value){
    mainGame->updateMethod();
    glutTimerFunc(16, updateMethod, 0);
    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y){
    if(btn == GLUT_LEFT_BUTTON){
        if(state == GLUT_DOWN){
            mainGame->screenClick(x, y);
        }
    }
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
        case 'j':
        case 'J':
            lightpos1[1] -= 1;
//            light_pos2[1] -= 10;
            break;
            // if 'u' -> increase light 1 brightness
        case 'u':
        case 'U':
            lightpos1[1] += 1;
//            light_pos2[1] += 10;
            break;
        case 'h':
        case 'H':
            lightpos1[2] += 1;
//            light_pos2[2] += 10;
            break;
        case 'K':
        case 'k':
            lightpos1[2] -= 1;
//            light_pos2[2] -= 10;
            break;
    }
    printf("%f %f %f\n", lightpos1[0], lightpos1[1], lightpos1[2]);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);
//    glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);
    glPopMatrix();
    
    glutPostRedisplay();
}

void init(void){
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glEnable(GL_COLOR_MATERIAL);
    
    glEnable(GL_LIGHTING);
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
//    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir);
    
    glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);
//    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDir);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDif);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpec);
    
    glLightfv(GL_LIGHT2, GL_POSITION, lightpos2);
    //    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightDir);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDif);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpec);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
//    glEnable(GL_LIGHT2);

    
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
    glutMouseFunc(mouse);
    
    glutTimerFunc(16, updateMethod, 0);
    
    glEnable(GL_DEPTH_TEST);
    init();
    glutMainLoop();
    return 0;
}

