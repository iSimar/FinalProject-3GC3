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


GLuint filter;                      // Which Filter To Use
GLuint fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR };   // Storage For Three Types Of Fog
GLuint fogfilter= 2;                    // Which Fog To Use
GLfloat fogColor[4]= {0.5f, 0.5f, 0.5f, 1.0f};      // Fog Color

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
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if(firstPersonMode==OFF)
        gluLookAt(camPos[0], camPos[1], camPos[2], 0,10,0, 0,1,0);
    else
        mainGame->setFPLook();
    
    mainGame->draw();
    
    glutSwapBuffers();
    
}

unsigned char* loadPPM(const char* filename, int& width, int& height){
    const int BUFSIZE = 128;
    FILE* fp;
    unsigned int read;
    unsigned char* rawData;
    char buf[3][BUFSIZE];
    char* retval_fgets;
    size_t retval_sscanf;
    
    if ( (fp=fopen(filename, "rb")) == NULL)
    {
        std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
        width = 0;
        height = 0;
        return NULL;
    }
    
    // Read magic number:
    retval_fgets = fgets(buf[0], BUFSIZE, fp);
    
    // Read width and height:
    do
    {
        retval_fgets=fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');
    retval_sscanf=sscanf(buf[0], "%s %s", buf[1], buf[2]);
    width  = atoi(buf[1]);
    height = atoi(buf[2]);
    
    // Read maxval:
    do
    {
        retval_fgets=fgets(buf[0], BUFSIZE, fp);
    } while (buf[0][0] == '#');
    
    // Read image data:
    rawData = new unsigned char[width * height * 3];
    read = fread(rawData, width * height * 3, 1, fp);
    fclose(fp);
    if (read != 1)
    {
        std::cerr << "error parsing ppm file, incomplete data" << std::endl;
        delete[] rawData;
        width = 0;
        height = 0;
        return NULL;
    }
    
    return rawData;
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
//
void initFog(){
    glClearColor(0.5f,0.5f,0.5f,1.0f);          // We'll Clear To The Color Of The Fog ( Modified )
    glFogi(GL_FOG_MODE, fogMode[fogfilter]);        // Fog Mode
    glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
    glFogf(GL_FOG_DENSITY, 0.2f);              // How Dense Will The Fog Be
    glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
    glFogf(GL_FOG_START, 0.0f);             // Fog Start Depth
    glFogf(GL_FOG_END, 100.0f);               // Fog End Depth
    glEnable(GL_FOG);                   // Enables GL_FOG
}

void init(void){
    initFog();
    
//    glClearColor(1, 1, 1, 0);
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

