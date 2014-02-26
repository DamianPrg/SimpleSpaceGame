//
//  Player.cpp
//  SimpleSpaceGame
//
//  Created by Damian Balandowski on 26.02.2014.
//  Copyright (c) 2014 Damian Balandowski. All rights reserved.
//

#include "Player.h"

#include "Game.h"

void Player::initialize()
{
    spaceShip.load("Gfx/player.png");
    shield.load("Gfx/shield.png");
    
    hasShield = false;
    rotation = 0.0f;
    
    name = "Player";
    shouldBeRemoved = false;
    
    ammo = startWithAmmo;
}

void Player::draw(sf::RenderWindow* renderWindow)
{
    if(hasShield)
    {
        shield().setPosition(spaceShip().getPosition());
        renderWindow->draw(shield());
    }
    
    renderWindow->draw(spaceShip());
}

void Player::update(float dt)
{
    static bool is_pressed = false;
    
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && is_pressed == false
       && ammo > 0)
    {
        Game.addProjectile(pos(), rotation);
        is_pressed = true;
        
        ammo--;
    }
    
    if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && is_pressed)
    {
        is_pressed = false;
    }

    
    sf::Vector2i mousePos = sf::Mouse::getPosition(Game.getWindow());
    sf::Vector2f convertedMP = Game.getWindow().mapPixelToCoords(mousePos);
    
    float _rot = atan2f(pos().y - convertedMP.y,
                        pos().x - convertedMP.x);
    
    rotation = -90+(180.0f/3.14f)*_rot;
    
    if(velocity.x > max_speed) velocity.x = max_speed;
    if(velocity.y > max_speed) velocity.y = max_speed;
    
    velocity.x -= velocity.x * smooth;
    velocity.y -= velocity.y * smooth;
    
    position.move(velocity.x, velocity.y);
    spaceShip().setPosition(position.x, position.y);
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x += speedApply;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x += -speedApply;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        velocity.y += -speedApply;
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        velocity.y += speedApply;
    }
    
    spaceShip().setRotation(rotation);
    shield().setRotation(rotation);
}

void Player::collision(std::shared_ptr<GameObject> gameObject,
               Vec2 col_pos)
{
    /*
    gameObject->vel().x += vel().x*0.29;
    gameObject->vel().y += vel().y*0.29;
    vel().x=-vel().x*0.2;
    vel().y=-vel().y*0.2;
     */
    if(gameObject->getName() == "Pickup")
    {
        std::shared_ptr<Pickup> pickup = std::dynamic_pointer_cast<Pickup>(gameObject);
        
        switch(pickup->getPickupType())
        {
            case Pickup::PT_AMMO:
            {
                ammo += 2;
            } break;
                
            case Pickup::PT_HEALTH:
            {
                
            } break;
                
            case Pickup::PT_SHIELD:
            {
                
            } break;
        }
        
        gameObject->setShouldBeRemoved(true);
    }
}