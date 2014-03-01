//
//  Enemy.cpp
//  SimpleSpaceGame
//
//  Created by Damian Balandowski on 01.03.2014.
//  Copyright (c) 2014 Damian Balandowski. All rights reserved.
//

#include "Enemy.h"

#include "Game.h"

void Enemy::initialize()
{
    ship.load("Gfx/enemyRed3.png");
    name = "Enemy";

    initializeDefault();
    
    pos().y = -240.0f;
}

void Enemy::update(float dt)
{
    if(shootTimer.getElapsedTime().asSeconds() > 1.5f)
    {
        shootTimer.restart();
        
        Game.addProjectile(pos(), -180.0f);
    }
    
    position.move(velocity.x, velocity.y);
    
    ship().setPosition(pos().x, pos().y);
}

void Enemy::draw(sf::RenderWindow* renderWindow)
{
    renderWindow->draw(ship());
}