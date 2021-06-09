#include "in_game_scene.h"

#include "effect.h"

Effect::Effect(void) {
    m_sprite = NULL;
}

Effect::~Effect(void) {
    destroy();
}

void Effect::create(InGameScene *scene, sf::RenderTarget *renderer, sf::Texture *splashTex, float lifetime) {
    m_scene = scene;
    m_renderer = renderer;
    m_splashTex = splashTex;
    m_lifetime = lifetime;
}

void Effect::initialize(void) {
    if (m_sprite == NULL) {
        m_sprite = new sf::Sprite(*m_splashTex);

        sf::FloatRect bounds = m_sprite->getLocalBounds();
        m_sprite->setOrigin(0.5f * bounds.width, 0.5f * bounds.height);
    }

    m_scale = sf::Vector2f(1.0f, 1.0f);
    m_rotation = 0.0f;
    m_position = sf::Vector2f();

    m_clock.restart();
}

void Effect::update(float dt) {
    if (m_sprite != NULL) {
        if (isAlive()) {
            m_sprite->setScale(m_scale);
            m_sprite->setRotation(m_rotation);
            m_sprite->setPosition(m_position);
        } else {
            destroy();
        }
    }
}

void Effect::render(float dt) {
    if ((m_sprite != NULL) && isAlive()) {
        m_renderer->draw(*m_sprite);
    }
}

void Effect::destroy(void) {
    if (m_sprite != NULL) {
        delete m_sprite;
        m_sprite = NULL;
    }
}

Scene *Effect::getScene(void) const {
    return static_cast<Scene *const>(m_scene);
}

unsigned int Effect::getUniqueID(void) const {
    return 0xD3E12D68;
}

sf::Vector2f Effect::getScale(void) const {
    return m_scale;
}

void Effect::setScale(const sf::Vector2f &scale) {
    m_scale = scale;
}

float Effect::getRotation(void) const {
    return m_rotation;
}

void Effect::setRotation(float rotation) {
    m_rotation = rotation;
}

sf::Vector2f Effect::getPosition(void) const {
    return m_position;
}

void Effect::setPosition(const sf::Vector2f &position) {
    m_position = position;
}

bool Effect::isAlive(void) const {
    return m_clock.getElapsedTime().asSeconds() < m_lifetime;
}


