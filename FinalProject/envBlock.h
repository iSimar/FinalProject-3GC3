//
//  envBlock.h
//  FinalProject
//
//  Created by Simar Singh on 2014-12-07.
//  Copyright (c) 2014 Simarpreet Singh. All rights reserved.
//

#include <stdio.h>

class envBlock{
public:
    float length;
    float width;
    float height;
    
    float translateZ;
    
    envBlock();
    envBlock(float l, float w, float h);
    
    void addToTranslateZ(float i);
    
    void draw();
};