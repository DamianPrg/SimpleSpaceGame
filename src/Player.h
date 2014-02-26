//
//  Player.h
//  SimpleSpaceGame
//
//  Created by Damian Balandowski on 26.02.2014.
//  Copyright (c) 2014 Damian Balandowski. All rights reserved.
//

#ifndef __SimpleSpaceGame__Player__
#define __SimpleSpaceGame__Player__

#include "GameObject.h"

class Player : public GameObject
{
public:
    void initialize();
    void draw(sf::RenderWindow* renderWindow);
    void update(float dt);
    void collision(std::shared_ptr<GameObject> gameObject,
                           Vec2 col_pos);
    
    int width() { return spaceShip.width(); }
    int height() { return spaceShip.height(); }
protected:
    Drawable spaceShip, shield;
    
    const float smooth     = 0.05f;
    const float max_speed  = 3.5f;
    const float speedApply = 0.4f;
    bool hasShield;
    
    int ammo;
    const int startWithAmmo = 3;
    
};

#endif /* defined(__SimpleSpaceGame__Player__) */
