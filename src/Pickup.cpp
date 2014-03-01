//
//  Pickup.cpp
//  SimpleSpaceGame
//
//  Created by Damian Balandowski on 26.02.2014.
//  Copyright (c) 2014 Damian Balandowski. All rights reserved.
//

#include "Pickup.h"

void Pickup::initialize()
{
    pickup.load(pickupGfxs[pickupType]);
    name = "Pickup";
    shouldBeRemoved = false;
}

void Pickup::update(float dt)
{
    // just rotate it?
    //rotation += dt*10.0f;
    //pickup().setRotation(rotation);
    static float alpha=100;
    static int dir  =1;
    
    alpha += (dir * 100) * dt;
    
    if(alpha > 230) {
        dir = -1;
    }
    if(alpha < 100) {
        dir = 1;
    }
    
    pickup().setColor(sf::Color(255,255,255,alpha));
    pickup().setPosition(pos().x, pos().y);
}

void Pickup::draw(sf::RenderWindow* renderWindow)
{
    renderWindow->draw(pickup());
}