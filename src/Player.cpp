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
    
    health = 255;
    loseSound.loadAsSound("Sfx/sfx_lose.ogg");
    
    hasMagnet = false;
    
    hitSound.loadAsSound("Sfx/sfx_twoTone.ogg");
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
        Game.addProjectile(pos(), rotation, getName());
        is_pressed = true;
        
        ammo--;
    }
    
    if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && is_pressed)
    {
        is_pressed = false;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && hasMagnet)
    {
        std::vector<std::shared_ptr<GameObject>> objs = Game.getNearObjects("Player", 300.0f);
        
        for(int i = 0; i < objs.size(); i++)
        {
            std::shared_ptr<GameObject> e = Game.getGameObject("Enemy");
            
            // velocity to enemy
            Vec2 vte = Vec2::velocity(objs[i]->pos(), e->pos()).normalized();
            
            objs[i]->vel().x = vte.x*1.4f;
            objs[i]->vel().y = vte.y*1.4f;
        }
        
        hasMagnet = false;
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
    
    spaceShip().setColor(sf::Color(255,255,255,health));
    
    if(health < 10) {
        spaceShip().setColor(sf::Color(255,255,255,10));
        loseSound.playAsSound();
        health=1000;
        Game.setGameState(GS_MENU);
    }
    
    if(health >= 255) {
        health = 255;
    }
    
}

void Player::collision(std::shared_ptr<GameObject> gameObject,
               Vec2 col_pos)
{
    if(gameObject->getName() == "Pickup")
    {
        std::shared_ptr<Pickup> pickup = std::dynamic_pointer_cast<Pickup>(gameObject);
        
        switch(pickup->getPickupType())
        {
            case Pickup::PT_AMMO:
            {
                ammo += 3;
            } break;
                
            case Pickup::PT_HEALTH:
            {
                health += 40;
            } break;
                
            case Pickup::PT_SHIELD:
            {
                hasShield = true;
            } break;
                
            case Pickup::PT_EXTRA:
            {
                hasMagnet = true;
            } break;
        }
        
        gameObject->setShouldBeRemoved(true);
    }
    
    if(gameObject->getName() == "Meteor")
    {
      
    }
    
    static int projCount=0;
    
    if(gameObject->getName() == "Projectile")
    {
        std::shared_ptr<Projectile> projc = std::dynamic_pointer_cast<Projectile>(gameObject);
        
        if(projc->getShooter() == "Enemy")
        {
            if(!hasShield)
            {
                health -= 20;
                hitSound.playAsSound();
            }
            else
            {
                projCount ++;
                
                // if player has shield, shoot projectile back
                
                projc->setShooter("Player");        // set shooter to player, so it takes damage to enemy.
                projc->vel().x = -projc->vel().x;
                projc->vel().y = -projc->vel().y;
                
                if(projCount >= 3) {
                    hasShield = false;
                    projCount = 0;
                }
                
            }
        }
    }
}