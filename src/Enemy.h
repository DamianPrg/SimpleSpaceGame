//
//  Enemy.h
//  SimpleSpaceGame
//
//  Created by Damian Balandowski on 01.03.2014.
//  Copyright (c) 2014 Damian Balandowski. All rights reserved.
//

#ifndef __SimpleSpaceGame__Enemy__
#define __SimpleSpaceGame__Enemy__

#include "GameObject.h"

class Enemy : public GameObject
{
public:
    void initialize();
    void update(float dt);
    void draw(sf::RenderWindow* renderWindow);
private:
    Drawable ship;
    sf::Clock shootTimer;
};

#endif /* defined(__SimpleSpaceGame__Enemy__) */
