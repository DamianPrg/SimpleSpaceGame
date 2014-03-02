//
//  Game.h
//  SimpleSpaceGame
//
//  Created by Damian Balandowski on 25.02.2014.
//  Copyright (c) 2014 Damian Balandowski. All rights reserved.
//

/*
 * Simple space shooter game, made in few hours.
 * Libs used: SFML 2
 *
 * Graphics: 'Kenney.nl'
 *
 */

#ifndef __SimpleSpaceGame__Game__
#define __SimpleSpaceGame__Game__

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameObject.h"
#include "Player.h"
#include "Meteor.h"
#include "Projectile.h"
#include "Pickup.h"
#include "Enemy.h"
#include <ctime>

// todo: cleanup projectiles, etc..,
//       fixes, better gameplay.
enum GAME_STATE { GS_GAME, GS_MENU, GS_OVER };

class CGame
{
public:
    void initialize();
    void draw();
    void update();
    
    void run();
    
    sf::View& getView() { return view; }
    sf::RenderWindow& getWindow() { return renderWindow; }
    
    void addProjectile(Vec2 pos, float rot, std::string shooter="unknown");
    void addPickup(Pickup::PICKUP_TYPE pt, Vec2 pos);
    void addGameObject(std::shared_ptr<GameObject> gameObject) {
        gameObjects.push_back(gameObject);
    }
    
    // returns first object of specified name
    std::shared_ptr<GameObject> getGameObject(std::string n) {
        for(int i = 0; i < gameObjects.size(); i++) {
            if(gameObjects[i]->getName() == n) {
                return gameObjects[i];
            }
        }
        
        return gameObjects[0];
    }
    
    std::vector<std::shared_ptr<GameObject>> getNearObjects(std::string n, float max_dist);
 
    void setGameState(GAME_STATE gs) {
        gameState = gs;
    }
private:
    GAME_STATE gameState;
    
    sf::RenderWindow renderWindow;
    sf::View         view;
    sf::Clock        clock;
    float            dt;
    
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    
    std::shared_ptr<Player> player;
    std::shared_ptr<Meteor> meteor;
    
    Drawable background, menuBackground;
    Sound    backgroundMusic, shootSound;
};

extern CGame Game;

#endif /* defined(__SimpleSpaceGame__Game__) */
