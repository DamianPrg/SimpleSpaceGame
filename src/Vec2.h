//
//  Vec2.h
//  SimpleSpaceGame
//
//  Created by Damian Balandowski on 26.02.2014.
//  Copyright (c) 2014 Damian Balandowski. All rights reserved.
//

#ifndef __SimpleSpaceGame__Vec2__
#define __SimpleSpaceGame__Vec2__

#include <iostream>
#include <cmath>

class Vec2
{
public:
    Vec2() {
        x=0.0f;y=0.0f;
    }
    Vec2(float a, float b):x(a),y(b) {}
    
    void operator()(float _x, float _y) {
        x = _x;
        y = _y;
    }
    
    void operator()(const Vec2& v) {
        x = v.x;
        y = v.y;
    }
    
    float length()
    {
        return sqrt(x*x+y*y);
    }
    
    Vec2 normalized()
    {
        Vec2 t(0.0f, 0.0f);
        t.x = x / length();
        t.y = y / length();
        return t;
    }
    
    static Vec2 velocity(Vec2 a, Vec2 b)
    {
        Vec2 t;
        t.x = b.x - a.x;
        t.y = b.y - a.y;
        t = t.normalized();
        return t;
    }
    
    void move(float _x=0.0f, float _y=0.0f)
    {
        x += _x;
        y += _y;
    }
    
    void move(const Vec2& v)
    {
        x += v.x;
        y += v.y;
    }
    
    void clamp( float min_x, float max_x,
               float min_y, float max_y ) {
        if(x > max_x) x = max_x;
        else if(x < min_x) x = min_x;
        
        if(y > max_y) y = max_y;
        else if(y < max_y) y = min_y;
    }
    
    float x,y;
    
protected:
    
};

bool bbCollision(Vec2 ap, Vec2 as,
                 Vec2 bp, Vec2 bs);
float dist(Vec2 a, Vec2 b);
bool  ppCollision(Vec2 ap, Vec2 as,
                  Vec2 bp, Vec2 bs);

#endif /* defined(__SimpleSpaceGame__Vec2__) */
