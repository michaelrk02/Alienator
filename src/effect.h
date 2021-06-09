#pragma once

#include "stdinc.h"
#include "scene_object.h"

class InGameScene;

class Effect : public SceneObject {
public:
    Effect(void);
    ~Effect(void);

    void create(InGameScene *scene, sf::RenderTarget *renderer, sf::Texture *splashTex, float lifetime);

    void initialize(void);
    void update(float dt);
    void render(float dt);
    void destroy(void);

    Scene *getScene(void) const;
    unsigned int getUniqueID(void) const;

    sf::Vector2f getScale(void) const;
    void setScale(const sf::Vector2f &scale);

    float getRotation(void) const;
    void setRotation(float rotation);

    sf::Vector2f getPosition(void) const;
    void setPosition(const sf::Vector2f &position);

    bool isAlive(void) const;

protected:
    SHARED_PTR InGameScene *m_scene;
    SHARED_PTR sf::RenderTarget *m_renderer;
    SHARED_PTR sf::Texture *m_splashTex;
    float m_lifetime;

    UNIQUE_PTR sf::Sprite *m_sprite;
    sf::Clock m_clock;

    sf::Vector2f m_scale;
    float m_rotation;
    sf::Vector2f m_position;
};

