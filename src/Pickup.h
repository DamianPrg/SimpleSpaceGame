//
//  Pickup.h
//  SimpleSpaceGame
//
//  Created by Damian Balandowski on 26.02.2014.
//  Copyright (c) 2014 Damian Balandowski. All rights reserved.
//

#ifndef __SimpleSpaceGame__Pickup__
#define __SimpleSpaceGame__Pickup__

#include "GameObject.h"

// ! Set pickup type before calling 'initialize()'
class Pickup : public GameObject
{
public:
    enum PICKUP_TYPE { PT_AMMO, PT_SHIELD, PT_HEALTH, PT_EXTRA } pickupType;
    
    void initialize();
    void update(float dt);
    void draw(sf::RenderWindow* renderWindow);
    void setPickupType(PICKUP_TYPE pt) { pickupType = pt; }
    PICKUP_TYPE getPickupType() { return pickupType; }
    
    int width() { return pickup.width(); }
    int height() { return pickup.height(); }
private:

    Drawable pickup;
    
    const std::vector<std::string> pickupGfxs = {
        "Gfx/powerupYellow_bolt.png", // PT_AMMO
        "Gfx/powerupYellow_shield.png", // PT_SHIELD
        "Gfx/pill_green.png", // PT_HEALTH
        "Gfx/powerupEXTRA.png" // PT_EXTRA
    };
    
};

#endif /* defined(__SimpleSpaceGame__Pickup__) */
