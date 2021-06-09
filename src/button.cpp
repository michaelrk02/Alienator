#include "alienator.h"
#include "scene.h"

#include "button.h"

Button::Button(void) {
    m_game = NULL;
    m_scene = NULL;
    m_renderer = NULL;
    m_display = NULL;
    m_pad = NULL;

    m_scale = sf::Vector2f(1.0f, 1.0f);
    m_rotation = 0.0f;
}

Button::~Button(void) {
    destroy();
}

void Button::create(Scene *scene, sf::RenderTarget *renderer, const std::string &text, const sf::Font *font, const sf::Color &primaryColor, const sf::Color &secondaryColor, unsigned int characterSize) {
    m_scene = scene;
    m_renderer = renderer;

    if (m_display == NULL) {
        m_display = new sf::Text;
        m_display->setFont(*font);
        m_display->setCharacterSize(characterSize);
    }

    if (m_pad == NULL) {
        m_pad = new sf::RectangleShape;
        m_pad->setOutlineThickness(characterSize / 8);
    }

    this->text = text;
    this->primaryColor = primaryColor;
    this->secondaryColor = secondaryColor;

    initialize();
}

void Button::initialize(void) {
    m_game = reinterpret_cast<Alienator *>(m_scene->getGame());
}

void Button::update(float dt) {
    m_display->setString(text);

    sf::FloatRect bounds = m_display->getLocalBounds();
    m_pad->setSize(sf::Vector2f(bounds.width + m_scale.x * 16.0f, bounds.height + m_scale.y * 16.0f));

    m_display->setScale(m_scale);
    m_display->setRotation(m_rotation);
    m_display->setPosition(m_position);

    m_pad->setScale(m_scale);
    m_pad->setRotation(m_rotation);
    m_pad->setPosition(m_position);

    if (isHovered()) {
        m_pad->setFillColor(secondaryColor);
        m_pad->setOutlineColor(primaryColor);
        m_display->setFillColor(primaryColor);
    } else {
        m_pad->setFillColor(primaryColor);
        m_pad->setOutlineColor(secondaryColor);
        m_display->setFillColor(secondaryColor);
    }
}

void Button::render(float dt) {
    m_renderer->draw(*m_pad);
    m_renderer->draw(*m_display);
}

void Button::destroy(void) {
    if (m_display != NULL) {
        delete m_display;
        m_display = NULL;
    }
    if (m_pad != NULL) {
        delete m_pad;
        m_pad = NULL;
    }
}

Scene *Button::getScene(void) const {
    return m_scene;
}

unsigned int Button::getUniqueID(void) const {
    return UID_BUTTON;
}

sf::Vector2f Button::getScale(void) const {
    return m_scale;
}

void Button::setScale(const sf::Vector2f &scale) {
    m_scale = scale;
}

float Button::getRotation(void) const {
    return m_rotation;
}

void Button::setRotation(float rotation) {
    m_rotation = rotation;
}

sf::Vector2f Button::getPosition(void) const {
    return m_position;
}

void Button::setPosition(const sf::Vector2f &position) {
    m_position = position;
}

sf::FloatRect Button::getBounds(void) const {
    return m_pad->getGlobalBounds();
}

bool Button::isHovered(void) const {
    sf::FloatRect rect = m_pad->getGlobalBounds();

    return rect.contains(m_game->getMouseLocation());
}

