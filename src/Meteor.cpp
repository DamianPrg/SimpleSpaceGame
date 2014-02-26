//
//  Meteor.cpp
//  SimpleSpaceGame
//
//  Created by Damian Balandowski on 26.02.2014.
//  Copyright (c) 2014 Damian Balandowski. All rights reserved.
//

#include "Meteor.h"

#include "Game.h"

void Meteor::initialize()
{
    // random meteor image
    std::string m = meteorGfxs[rand() % meteorGfxs.size()];
    
    position.x = float(rand() % 1000)-500;
    position.y = float(rand() % 700)-300;
    
    // random velocity
    float x = float(rand() % 2000)-1000;
    float y = float(rand() % 2000)-1000;
    
    Vec2 vec(x,y);
    vec = vec.normalized();
    
    velocity.x = vec.x;
    velocity.y = vec.y;
    
    meteor.load(m);
    
    name = "Meteor";
    shouldBeRemoved = false;
}

void Meteor::draw(sf::RenderWindow* renderWindow)
{
    renderWindow->draw(meteor());
}

void Meteor::update(float dt)
{
    position.move(velocity.x * speed * dt,
                  velocity.y * speed * dt);
    
    meteor().setPosition(position.x, position.y);
    
    rotation += dt * rotSpeed;
    
    meteor().setRotation(rotation);

    
    /*
    if(position.x+width()/2 > Game.getView().getCenter().x + Game.getWindow().getSize().x/2)
    {
        vel().x = -vel().x;
    }
    
    if(position.x-width()/2 < Game.getView().getCenter().x - Game.getWindow().getSize().x/2)
    {
        vel().x = -vel().x;
    }
     */
    
    /*
    if(position.y+height()/2 > Game.getView().getCenter().y + Game.getWindow().getSize().y/2)
    {
        vel().y = -vel().y;
    }
    
    if(position.y-height()/2 < Game.getView().getCenter().y + Game.getWindow().getSize().y/2)
    {
        vel().y = -vel().y;
    }
     */
     
}

void Meteor::collision(std::shared_ptr<GameObject> gameObject,
                       Vec2 col_pos)
{
    // check if collision was with projectile
    if(gameObject->getName() == "Projectile")
    {
       this->setShouldBeRemoved(true);
       gameObject->setShouldBeRemoved(true);
        
        int luckyNumber=rand()%14;
        
        if(luckyNumber==4) {
            Game.addPickup(Pickup::PT_AMMO, pos());
        }
        
        if(luckyNumber==2) {
            Game.addPickup(Pickup::PT_HEALTH, pos());
        }
        
        if(luckyNumber==10) {
            Game.addPickup(Pickup::PT_SHIELD, pos());
        }
    }
    
    // someone friendly on the way?
    if(gameObject->getName() == "Meteor")
    {
        setShouldBeRemoved(true);
        gameObject->setShouldBeRemoved(true);
    }
}