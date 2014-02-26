//
//  Meteor.h
//  SimpleSpaceGame
//
//  Created by Damian Balandowski on 26.02.2014.
//  Copyright (c) 2014 Damian Balandowski. All rights reserved.
//

#ifndef __SimpleSpaceGame__Meteor__
#define __SimpleSpaceGame__Meteor__

#include "GameObject.h"

class Meteor : public GameObject
{
public:
    void initialize();
    void draw(sf::RenderWindow* renderWindow);
    void update(float dt);
    
    int width() { return meteor.width(); }
    int height() { return meteor.height(); }
    
    virtual void collision(std::shared_ptr<GameObject> gameObject,
                           Vec2 col_pos);
private:
    Drawable meteor;
    const std::vector<std::string> meteorGfxs = {
        "Gfx/meteorBrown_big1.png",
        "Gfx/meteorBrown_big2.png",
        "Gfx/meteorBrown_med1.png",
        "Gfx/meteorBrown_med3.png",
        "Gfx/meteorBrown_small2.png",
        "Gfx/meteorGrey_small1.png",
        "Gfx/meteorGrey_med1.png"
    };
    
    const float rotSpeed = 15.0f;
    const float speed    = 15.0f;
};

#endif /* defined(__SimpleSpaceGame__Meteor__) */
