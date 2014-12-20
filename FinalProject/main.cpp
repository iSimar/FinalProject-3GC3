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

int gamestatus = 0;

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
    
    if(firstPersonMode==OFF && gamestatus==1){
        gluLookAt(camPos[0], camPos[1], camPos[2], 0,10,0, 0,1,0);
        mainGame->draw();
    }else if(gamestatus==1){
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(450, 1, 1, 1000);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        mainGame->setFPLook();
        mainGame->draw();
        
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        mainGame->drawStrokeText((char*)"Score:", 400-180, 555);
        char* score = (char*)mainGame->setScore().c_str();
        mainGame->drawStrokeText(score, 500-180, 555);
        mainGame->drawStrokeText((char*)"Balls Left:", 400-180, 525);
        char* ballLeft = (char*)mainGame->setBallsLeft().c_str();
        mainGame->drawStrokeText(ballLeft, 550-180, 525);
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glEnable(GL_TEXTURE_2D);
        
    }else if(gamestatus==0){
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, 200, 0, 200);
        
        void * font1 = GLUT_BITMAP_TIMES_ROMAN_24;
        void * font2 = GLUT_BITMAP_9_BY_15;
        void * font3 = GLUT_BITMAP_TIMES_ROMAN_10;
        
        //Title
        glColor3f(1, 0, 0);
        glRasterPos2i(70, 170);
        string title = "WALL BLASTER";
        for (string::iterator i = title.begin(); i != title.end(); ++i){
            char c = *i;
            glutBitmapCharacter(font1, c);
        }
        //Instruction line 1
        glColor3f(1, 1, 1);
        glRasterPos2i(15, 130);
        string desc1 = "CLICK TO FIRE BALLS. BREAK THE GLASS PLANES THAT COME AT YOU. IF YOU GET HIT BY ONE, YOU LOSE.";
        for (string::iterator i = desc1.begin(); i != desc1.end(); ++i){
            char c = *i;
            glutBitmapCharacter(font3, c);
        }
        //Instruction line 2
        glRasterPos2i(15, 120);
        string desc2 = "HITTING ONE OF THE MANY PYRAMIDS ON THE FLOOR WILL ADD THREE BALLS TO YOUR TOTAL BALL AMMO";
        for (string::iterator i = desc2.begin(); i != desc2.end(); ++i){
            char c = *i;
            glutBitmapCharacter(font3, c);
        }
        //S
        glRasterPos2i(80, 80);
        string start = "(S)";
        for (string::iterator i = start.begin(); i != start.end(); ++i){
            char c = *i;
            glutBitmapCharacter(font2, c);
        }
        //Q
        glRasterPos2i(80, 60);
        string quit = "(Q)";
        for (string::iterator i = quit.begin(); i != quit.end(); ++i){
            char c = *i;
            glutBitmapCharacter(font2, c);
        }
        //Start
        glColor3f(0, 0.5, 1);
        glRasterPos2i(90, 80);
        string start2 = "Start";
        for (string::iterator i = start2.begin(); i != start2.end(); ++i){
            char c = *i;
            glutBitmapCharacter(font2, c);
        }
        //Quit
        glRasterPos2i(90, 60);
        string quit2 = "Quit";
        for (string::iterator i = quit2.begin(); i != quit2.end(); ++i){
            char c = *i;
            glutBitmapCharacter(font2, c);
        }
        //Name
        glColor3f(1, 1, 1);
        glRasterPos2i(15, 10);
        string name = "BY: Simarpreet Singh (1216728), Birunthaa Umamahesan (1203142), Joseph Nguyen (1229287), Curran Tam (1231038)";
        for (string::iterator i = name.begin(); i != name.end(); ++i){
            char c = *i;
            glutBitmapCharacter(font3, c);
        }
    }else if(gamestatus == 2){
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, 200, 0, 200);
        
        //Pause Menu
        glColor3f(1, 1, 1);
        glRasterPos2i(80, 100);
        string pause = "PAUSED";
        void * font1 = GLUT_BITMAP_TIMES_ROMAN_24;
        for (string::iterator i = pause.begin(); i != pause.end(); ++i){
            char c = *i;
            glutBitmapCharacter(font1, c);
        }
        //additional description
        glRasterPos2i(60, 70);
        void * font3 = GLUT_BITMAP_TIMES_ROMAN_10;
        string desc2 = "PRESS (S) TO RESTART THE GAME OR (Q) TO QUIT";
        for (string::iterator i = desc2.begin(); i != desc2.end(); ++i){
            char c = *i;
            glutBitmapCharacter(font3, c);
        }
    }
    else if(gamestatus == 3){
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, 200, 0, 200);
        //GAMEOVER
        glColor3f(1, 0, 0);
        glRasterPos2i(80, 100);
        string gameover = "GAME OVER";
        void * font1 = GLUT_BITMAP_TIMES_ROMAN_24;
        for (string::iterator i = gameover.begin(); i != gameover.end(); ++i){
            char c = *i;
            glutBitmapCharacter(font1, c);
        }
        glRasterPos2i(20, 130);
        string gameover2 = "YOU HIT A GLASS OR RAN OUT OF BALLS!";
        for (string::iterator i = gameover2.begin(); i != gameover2.end(); ++i){
            char c = *i;
            glutBitmapCharacter(font1, c);
        }
        //additional description
        glColor3f(1, 1, 1);
        glRasterPos2i(60, 70);
        void * font3 = GLUT_BITMAP_TIMES_ROMAN_10;
        string desc2 = "PRESS (S) TO RESTART THE GAME OR (Q) TO QUIT";
        for (string::iterator i = desc2.begin(); i != desc2.end(); ++i){
            char c = *i;
            glutBitmapCharacter(font3, c);
        }
    }
    
    
    
    glFlush();
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
//        std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
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
        delete[] rawData;
        width = 0;
        height = 0;
        return NULL;
    }
    
    return rawData;
}

void updateMethod(int value){
    mainGame->updateMethod();
    if(gamestatus==1){
        glutTimerFunc(16, updateMethod, 0);
        if(mainGame->isGameOver)
            gamestatus = 3;
    }
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
//                firstPersonMode = ON;
//                glMatrixMode(GL_PROJECTION);
//                glLoadIdentity();
//                gluPerspective(45, 1, 1, 100);
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
        case 'S':
        case 's':
            if(gamestatus != 1){
                gamestatus = 1;
                mainGame = new game();
                glutTimerFunc(16, updateMethod, 0);
            }
            break;
        case 'P':
        case 'p':
            if(gamestatus != 2){
                gamestatus = 2;
            }else{
                gamestatus = 1;
                glutTimerFunc(16, updateMethod, 0);
            }
            break;
    }
//    printf("%f %f %f\n", lightpos1[0], lightpos1[1], lightpos1[2]);
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
    glFogf(GL_FOG_DENSITY, 0.9f);              // How Dense Will The Fog Be
    glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
    glFogf(GL_FOG_START, 20.0f);             // Fog Start Depth
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
    
    glEnable(GL_TEXTURE_2D);   // enable texture mapping
    glShadeModel(GL_SMOOTH);   // enable smooth shading
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // black background
    glClearDepth(1.0f);        // depth buffer setup
    glDepthFunc(GL_LEQUAL);    // configure depth testing
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // really nice perspective calculations
}

void loadTexture(){
    GLuint texture[1];     // storage for one texture
    int twidth, theight;   // texture width/height [pixels]
    unsigned char* tdata;  // texture pixel data
    
    // Load image file
    tdata = loadPPM("Brickwall.ppm", twidth, theight);
    if (tdata==NULL) return;
    
    // Create ID for texture
    glGenTextures(1, &texture[0]);
    
    // Set this texture to be the one we are working with
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    
    // Generate the texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);
    
    // Set bi-linear filtering for both minification and magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
    loadTexture();
    init();
    glutMainLoop();
    return 0;
}

