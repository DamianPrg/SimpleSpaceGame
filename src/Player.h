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
    Sound    loseSound, hitSound;
    
    const float smooth     = 0.03f;// default:0.05f
    const float max_speed  = 7.0f; // default:5.0f
    const float speedApply = 0.6f; // default:0.4f
    
    bool hasShield;
    bool hasMagnet;
    
    int ammo;
    const int startWithAmmo = 30;
    
    int health;
    

};

#endif /* defined(__SimpleSpaceGame__Player__) */
