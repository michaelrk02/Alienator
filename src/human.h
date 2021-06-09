#pragma once

#include "stdinc.h"
#include "scene_object.h"

class InGameScene;
class Weapon;

class Human : public SceneObject {
public:
    Human(void);
    ~Human(void);

    void create(InGameScene *scene, sf::RenderTarget *renderer, sf::Texture *shipTex, sf::Texture *minigunTex, sf::Texture *laserFlashTex, sf::Texture *minigunFlashTex, sf::Texture *laserProjTex, sf::Texture *minigunProjTex, sf::SoundBuffer *laserSnd, sf::SoundBuffer *minigunSnd);

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

    float getRadius(void) const;

protected:
    SHARED_PTR InGameScene *m_scene;
    SHARED_PTR sf::RenderTarget *m_renderer;
    SHARED_PTR sf::Texture *m_shipTex;
    SHARED_PTR sf::Texture *m_minigunTex;
    SHARED_PTR sf::Texture *m_laserFlashTex;
    SHARED_PTR sf::Texture *m_minigunFlashTex;
    SHARED_PTR sf::Texture *m_laserProjTex;
    SHARED_PTR sf::Texture *m_minigunProjTex;
    SHARED_PTR sf::SoundBuffer *m_laserSnd;
    SHARED_PTR sf::SoundBuffer *m_minigunSnd;

    UNIQUE_PTR sf::Sprite *m_ship;
    UNIQUE_PTR sf::Sprite *m_minigun;

    UNIQUE_PTR Weapon *m_laserWpn;
    UNIQUE_PTR Weapon *m_minigunWpn;

    sf::Vector2f m_position;

    float m_shipRotation;
    sf::Vector2f m_shipDirection;

    float m_minigunRotation;
    sf::Vector2f m_minigunDirection;

    float m_radius;
    float m_moveSpeed;
    float m_rotateSpeed;
};

