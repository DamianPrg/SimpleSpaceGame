//
//  Projectile.h
//  SimpleSpaceGame
//
//  Created by Damian Balandowski on 26.02.2014.
//  Copyright (c) 2014 Damian Balandowski. All rights reserved.
//

#ifndef __SimpleSpaceGame__Projectile__
#define __SimpleSpaceGame__Projectile__

#include "GameObject.h"

class Projectile : public GameObject
{
public:
    void initialize();
    void draw(sf::RenderWindow* renderWindow);
    void update(float dt);
private:
    Drawable projGfx;
    const float speed = 17.0f;
};

#endif /* defined(__SimpleSpaceGame__Projectile__) */
