//
//  GameObjecrt.cpp
//  SimpleSpaceGame
//
//  Created by Damian Balandowski on 26.02.2014.
//  Copyright (c) 2014 Damian Balandowski. All rights reserved.
//

#include "GameObject.h"

void GameObject::initializeDefault()
{
    shouldBeRemoved = false;
    rotation = 0.0f;
    position = Vec2(0.0f,0.0f);
    velocity = Vec2(0.0f,0.0f);
}