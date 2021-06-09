#pragma once

#include "game_object.h"

class Scene : public GameObject {
public:
    virtual void handle(const sf::Event *event) = 0;

    virtual void loadResources(void) = 0;
    virtual void unloadResources(void) = 0;

    virtual GameObject *getGame(void) const = 0;
};

