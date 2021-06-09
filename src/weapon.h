#pragma once

#include <list>

#include "stdinc.h"
#include "scene_object.h"

class MuzzleFlashEffect;
class Projectile;

class Weapon : public SceneObject {
public:
    Weapon(void);
    ~Weapon(void);

    void create(InGameScene *scene, sf::RenderTarget *renderer, sf::SoundBuffer *fireSnd, sf::Texture *muzzleFlashFxTex, sf::Texture *projectileTex, float fireRate, float muzzleFlashLifetime, float projectileSpeed, float projectileRange, float accuracy);

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

    bool canFire(void);

    void fire(void);

protected:
    SHARED_PTR InGameScene *m_scene;
    SHARED_PTR sf::RenderTarget *m_renderer;
    SHARED_PTR sf::SoundBuffer *m_fireSnd;
    SHARED_PTR sf::Texture *m_muzzleFlashFxTex;
    SHARED_PTR sf::Texture *m_projectileTex;

    float m_fireRate;
    float m_muzzleFlashLifetime;
    sf::Clock m_fireClock;
    float m_projectileSpeed;
    float m_projectileRange;
    float m_accuracy;

    UNIQUE_PTR sf::Sound *m_sound;
    UNIQUE_PTR MuzzleFlashEffect *m_muzzleFlash;

    float m_rotation;
    sf::Vector2f m_position;

    std::list<UNIQUE_PTR Projectile *> m_projectiles;
};

