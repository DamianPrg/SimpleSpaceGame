//
//  Projectile.cpp
//  SimpleSpaceGame
//
//  Created by Damian Balandowski on 26.02.2014.
//  Copyright (c) 2014 Damian Balandowski. All rights reserved.
//

#include "Projectile.h"

void Projectile::initialize()
{
    projGfx.load("Gfx/laserRed.png");
    
    name = "Projectile";
    
    shouldBeRemoved = false;
    shooter = "Unknown";
}

void Projectile::draw(sf::RenderWindow* renderWindow)
{
    renderWindow->draw(projGfx());
}

void Projectile::update(float dt)
{
    position.move(velocity.x * speed,
                  velocity.y * speed);
    projGfx().setPosition(position.x, position.y);
}