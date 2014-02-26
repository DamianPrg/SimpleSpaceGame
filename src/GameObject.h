//
//  GameObjecrt.h
//  SimpleSpaceGame
//
//  Created by Damian Balandowski on 26.02.2014.
//  Copyright (c) 2014 Damian Balandowski. All rights reserved.
//

#ifndef __SimpleSpaceGame__GameObjecrt__
#define __SimpleSpaceGame__GameObjecrt__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Vec2.h"

struct Drawable
{
    sf::Texture texture;
    sf::Sprite  sprite;
    
    void load(std::string filename) {
        texture.loadFromFile(filename);
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x/2,
                         texture.getSize().y/2);

    }
    
    int width() { return texture.getSize().x; }
    int height() { return texture.getSize().y; }
    
    sf::Sprite& operator ()() { return sprite; }
};

class GameObject
{
public:
    virtual void initialize() = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow* renderWindow) = 0;
    
    virtual void collision(std::shared_ptr<GameObject> gameObject,
                           Vec2 col_pos){}
    
    virtual int  width() {return 0;}
    virtual int  height() {return 0;}
    Vec2&         pos() { return position; }
    Vec2&         vel() { return velocity; }
    std::string   getName() { return name; }
    bool getShouldBeRemoved() { return shouldBeRemoved; }
    
    void setShouldBeRemoved(bool a) { shouldBeRemoved = a; }
protected:
    Vec2 position, velocity;
    float rotation;
    std::string name;
    bool shouldBeRemoved;
};

#endif /* defined(__SimpleSpaceGame__GameObjecrt__) */
