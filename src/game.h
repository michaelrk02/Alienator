#pragma once

#include "game_object.h"

class Scene;

class Game : public GameObject {
public:
    virtual bool isRunning(void) const = 0;
    virtual void setRunning(bool running) = 0;

    virtual Scene *getScene(void) const = 0;
    virtual void setScene(Scene *scene) = 0;
};

