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
    void collision(std::shared_ptr<GameObject> gameObject, Vec2 col_pos);
    
    int width() { return ship.width(); }
    int height() { return ship.height(); }
private:
    Drawable ship;
    sf::Clock shootTimer;
    
    const float rotSpeed = 60.0f;
    const float speed    = 100.0f;
    int   health;
    float accel;
};

#endif /* defined(__SimpleSpaceGame__Enemy__) */
