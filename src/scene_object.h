#pragma once

#include <SFML/System.hpp>

#include "game_object.h"

class Scene;

class SceneObject : public GameObject {
public:
    virtual Scene *getScene(void) const = 0;
    virtual unsigned int getUniqueID(void) const = 0;

    virtual sf::Vector2f getScale(void) const = 0;
    virtual void setScale(const sf::Vector2f &scale) = 0;

    virtual float getRotation(void) const = 0;
    virtual void setRotation(float rotation) = 0;

    virtual sf::Vector2f getPosition(void) const = 0;
    virtual void setPosition(const sf::Vector2f &position) = 0;
};

