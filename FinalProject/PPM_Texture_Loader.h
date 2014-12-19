//
//  PPM_Texture_Loader.h
//  FinalProject
//
//  Created by Birunthaa Uma on 14-12-19.
//  Copyright (c) 2014 Simarpreet Singh. All rights reserved.
//

#ifndef __FinalProject__PPM_Texture_Loader__
#define __FinalProject__PPM_Texture_Loader__

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

GLubyte* LoadPPM(char* file, int* width, int* height, int* max);

void LoadTextures(GLuint *textureID);

#endif /* defined(__FinalProject__PPM_Texture_Loader__) */
