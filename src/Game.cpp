//
//  Game.cpp
//  SimpleSpaceGame
//
//  Created by Damian Balandowski on 25.02.2014.
//  Copyright (c) 2014 Damian Balandowski. All rights reserved.
//

#include "Game.h"

void CGame::initialize()
{
    std::srand( time(NULL) );
    
    renderWindow.create(sf::VideoMode(1024,780),
                        "Space Shooter Game by Damian Balandowski");
    
    renderWindow.setFramerateLimit(60);
    renderWindow.setVerticalSyncEnabled(true);
    
    // create view/camera
    view.setSize(renderWindow.getSize().x,
                 renderWindow.getSize().y);
    
    view.setCenter(0.0f, 0.0f);
    renderWindow.setView(view);
    
    background.load("Gfx/darkPurple.png");
    
    //------------
    player = std::make_shared<Player>();
    player->initialize();
    
    meteor = std::make_shared<Meteor>();
    meteor->initialize();
    
    gameObjects.push_back(player);
    gameObjects.push_back(meteor);
    
    // generate meteors
    for(int i = 0; i < 20; i++)
    {
        std::shared_ptr<Meteor> m = std::make_shared<Meteor>();
        m->initialize();
        gameObjects.push_back(m);
    }

    for(int i = 0; i < 1; i++)
    {
        std::shared_ptr<Enemy> e = std::make_shared<Enemy>();
        e->initialize();
        gameObjects.push_back(e);
    }
    
    addPickup(Pickup::PICKUP_TYPE::PT_AMMO, Vec2(20.0f, 20.0f));
    
    backgroundMusic.loadAsMusic("Sfx/Spacecrusher_0.ogg");
    shootSound.loadAsSound("Sfx/sfx_laser1.ogg");
    //backgroundMusic.playAsMusic();
}

void CGame::addProjectile(Vec2 pos, float rot)
{
    std::shared_ptr<Projectile> projectile = std::make_shared<Projectile>();
    projectile->initialize();
    projectile->pos().x = pos.x;
    projectile->pos().y = pos.y;
    
    projectile->vel().x = sin((3.14f/180.0f)*rot);
    projectile->vel().y = -cos((3.14f/180.0f)*rot);
    
    shootSound.playAsSound();
    
    gameObjects.push_back(projectile);
}

void CGame::addPickup(Pickup::PICKUP_TYPE pt, Vec2 pos)
{
    std::shared_ptr<Pickup> pickup = std::make_shared<Pickup>();
    pickup->setPickupType(pt);
    pickup->pos().x = pos.x;
    pickup->pos().y = pos.y;
    pickup->initialize();
    
    gameObjects.push_back(pickup);
}

void CGame::update()
{
    // look for objects which need to be removed
    for(int i = 0; i < gameObjects.size(); i++)
    {
        if(gameObjects[i]->getShouldBeRemoved())
        {
            gameObjects.erase(gameObjects.begin()+i);
        }
    }
    
    for(int i = 0; i < gameObjects.size(); i++)
    {
        for(int j = 0; j < gameObjects.size(); j++)
        {
            if(gameObjects[i] != gameObjects[j])
            {
                std::shared_ptr<GameObject> gA = gameObjects[i];
                std::shared_ptr<GameObject> gB = gameObjects[j];
                
                /*
                if(bbCollision(Vec2(gA->pos().x,
                                    gA->pos().y),
                               Vec2(gA->width(),gA->height()),
                               Vec2(gB->pos().x,
                                    gB->pos().y),
                               Vec2(gB->width(),gB->height())))
                {
                    gA->collision(gB, gA->pos());
                   // gB->collision(gA, gB->pos());
                }
                */
                if(ppCollision(Vec2(gA->pos().x,
                                    gA->pos().y),
                               Vec2(gA->width(),gA->height()),
                               Vec2(gB->pos().x,
                                    gB->pos().y),
                               Vec2(gB->width(),gB->height())))
                {
                    gA->collision(gB, gA->pos());
                    // gB->collision(gA, gB->pos());
                }
            }
        }
    }
    
    for(int i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->update(dt);
    }
}

void CGame::draw()
{
    // draw background
    for(int x = -10; x < 10; x++)
    {
        for(int y = -10; y < 10; y++)
        {
            float a = x * 256.0f;
            float b = y * 256.0f;
            
            background().setPosition(a, b);
            renderWindow.draw(background());
        }
    }
    
    for(int i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->draw(&renderWindow);
    }
}

void CGame::run()
{
    initialize();
    
    while(renderWindow.isOpen())
    {
        sf::Event event;
        renderWindow.pollEvent(event);

        
        if(event.type == sf::Event::Closed) renderWindow.close();
        
        update();
        
        renderWindow.clear(sf::Color(25,25,35));
        draw();
        renderWindow.display();
        
        dt = clock.restart().asSeconds();
    }
}

CGame Game;