//
//  Vec2.cpp
//  SimpleSpaceGame
//
//  Created by Damian Balandowski on 26.02.2014.
//  Copyright (c) 2014 Damian Balandowski. All rights reserved.
//

#include "Vec2.h"

bool bbCollision(Vec2 ap, Vec2 as,
                 Vec2 bp, Vec2 bs)
{
    float aw = as.x * 0.5;
    float bw = as.x * 0.5;
    
    float ah = as.y * 0.5;
    float bh = bs.y * 0.5;
    
    if(ap.x + aw > bp.x - aw && ap.x - aw < bp.x + bw &&
       ap.y + ah > bp.y - bh && ap.y - bh < bp.y + bh)
    {
        return true;
    }
    
    return false;
}

float dist(Vec2 a, Vec2 b)
{
    Vec2 t;
    
    t.x = b.x - a.x;
    t.y = b.y - a.y;
    
    return abs(t.length());
}

bool  ppCollision(Vec2 ap, Vec2 as,
                  Vec2 bp, Vec2 bs)
{
    float w = (as.x*0.5)+(bs.x*0.5);
    float h = (as.y*0.5)+(bs.y*0.5);
    
    float avg = (w+h)/2.0;
    
    if(dist(ap, bp) < avg+4.0f) {
        return true;
    }
    
    return false;
}