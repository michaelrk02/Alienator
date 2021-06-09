#pragma once

class GameObject {
public:
    virtual void initialize(void) = 0;
    virtual void update(float dt) = 0;
    virtual void render(float dt) = 0;
    virtual void destroy(void) = 0;
};

