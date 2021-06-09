#pragma once

#include "stdinc.h"
#include "scene_object.h"

class InGameScene;

class Projectile : public SceneObject {
public:
    Projectile(void);
    ~Projectile(void);

    void create(InGameScene *scene, sf::RenderTarget *renderer, sf::Texture *texture, float range);

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

    sf::Vector2f spawnPosition;
    sf::Vector2f direction;
    float speed;

protected:
    SHARED_PTR InGameScene *m_scene;
    SHARED_PTR sf::RenderTarget *m_renderer;
    SHARED_PTR sf::Texture *m_texture;

    UNIQUE_PTR sf::Sprite *m_sprite;
    float m_range;

    sf::Vector2f m_scale;
    sf::Vector2f m_position;
};

