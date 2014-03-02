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
    
    health = 255;
    
    rotation=rand()%360;
    
    pos().x = -500 + rand() % 1000;
    pos().y = -500 + rand() % 1000;
    
    accel = 0.5f;
}

void Enemy::update(float dt)
{
    if(shootTimer.getElapsedTime().asSeconds() > 1.6f)
    {
        shootTimer.restart();
        
        Game.addProjectile(pos(), rotation, getName());
    }
    
    Vec2 playerPos = Game.getGameObject("Player")->pos();
    
    float rotToPlayer = (180.0f/3.14f)*atan2f(playerPos.y-pos().y, playerPos.x-pos().x);
    
    
    float rotateTo = rotToPlayer+90.0f;
    
    //rotation = rotToPlayer+90.0f;
    
    if(dist(playerPos, pos()) > 220.0f)
    {
        if(rotation+2.0f < rotateTo) {
            rotation += rotSpeed * dt;
        }
    
        if(rotation-2.0f > rotateTo) {
            rotation -= rotSpeed * dt;
        }
    }
    else
    {
        if(rotation+2.0f < rotateTo) {
            rotation += rotSpeed*3.0f * dt;
        }
        
        if(rotation-2.0f > rotateTo) {
            rotation -= rotSpeed*3.0f * dt;
        }
    }
    
    // find random point near player
    Vec2 moveToPos;
    moveToPos.x = playerPos.x + -100 + (rand()%200);
    moveToPos.y = playerPos.y + -100 + (rand()%200);
    
    Vec2 velo = Vec2::velocity(pos(), moveToPos);
    
    vel().x = velo.x;
    vel().y = velo.y;

    
    /*
    static float velx=1.0f;

    rotation += velx;
    
    if(rotation > 30.0f) {
        velx=-1.0f;
    }
    if(rotation < -30.0f) {
        velx=1.0f;
    }*/
    
    ship().setRotation(rotation);
    
    position.move(velocity.x*speed*accel*dt, velocity.y*speed*accel*dt);
    
    ship().setPosition(pos().x, pos().y);
    
    ship().setColor(sf::Color(255,255,255,health));
    
    if(health < 1) {
        ship().setColor(sf::Color(255,255,255,0));
        setShouldBeRemoved(true);
        
        // Spawn new enemy
        std::shared_ptr<Enemy> e = std::make_shared<Enemy>();
        e->initialize();
        
        Game.addGameObject(e);
    }
    
    if(dist(pos(), Game.getGameObject("Player")->pos()) < 400.0f) {
        accel = 0.5f;
    }
    else {
        accel = 1.0f;
    }
    
    // get objects
    std::vector<std::shared_ptr<GameObject>> objs = Game.getNearObjects("Enemy", 200.0f);
    
    for(int i = 0; i < objs.size(); i++)
    {
        if(objs[i]->getName() == "Projectile")
        {
            std::shared_ptr<Projectile> p = std::dynamic_pointer_cast<Projectile>(objs[i]);
            
            if(p->getShooter() == "Player")
            {
               
            }
        }
    }
    
}

void Enemy::draw(sf::RenderWindow* renderWindow)
{
    renderWindow->draw(ship());
}

void Enemy::collision(std::shared_ptr<GameObject> gameObject, Vec2 col_pos)
{
    if(gameObject->getName() == "Projectile")
    {
        std::shared_ptr<Projectile> projc = std::dynamic_pointer_cast<Projectile>(gameObject);
        
        if(projc->getShooter() == "Player")
        {
            health -= 30;
            gameObject->setShouldBeRemoved(true);
        }
    }
}