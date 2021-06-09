#pragma once

#include "stdinc.h"

#include "scene_object.h"

#define UID_BUTTON  0xE9B68A0B

class Button : public SceneObject {
public:
    Button(void);
    ~Button(void);

    void create(Scene *scene, sf::RenderTarget *renderer, const std::string &text, const sf::Font *font, const sf::Color &primaryColor, const sf::Color &secondaryColor, unsigned int characterSize);

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

    sf::FloatRect getBounds(void) const;

    bool isHovered(void) const;

    std::string text;
    sf::Color primaryColor;
    sf::Color secondaryColor;

protected:
    SHARED_PTR Alienator *m_game;

    SHARED_PTR Scene *m_scene;
    SHARED_PTR sf::RenderTarget *m_renderer;
    UNIQUE_PTR sf::Text *m_display;
    UNIQUE_PTR sf::RectangleShape *m_pad;

    sf::Vector2f m_scale;
    float m_rotation;
    sf::Vector2f m_position;
};

