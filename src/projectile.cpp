#include "in_game_scene.h"

#include "projectile.h"

Projectile::Projectile(void) {
    m_sprite = NULL;
}

Projectile::~Projectile(void) {
    destroy();
}

void Projectile::create(InGameScene *scene, sf::RenderTarget *renderer, sf::Texture *texture, float range) {
    m_scene = scene;
    m_renderer = renderer;
    m_texture = texture;
    m_range = range;
}

void Projectile::initialize(void) {
    m_scale = sf::Vector2f(1.0f, 1.0f);
    m_position = spawnPosition;

    if (m_sprite == NULL) {
        m_sprite = new sf::Sprite(*m_texture);

        sf::FloatRect bounds = m_sprite->getLocalBounds();
        m_sprite->setOrigin(0.5f * bounds.width, 0.5f * bounds.height);
    }
}

void Projectile::update(float dt) {
    if (m_sprite != NULL) {
        if (isAlive()) {
            m_position = m_position + speed * direction * dt;

            m_sprite->setScale(m_scale);
            m_sprite->setRotation(getRotation());
            m_sprite->setPosition(m_position);
        } else {
            destroy();
        }
    }
}

void Projectile::render(float dt) {
    if ((m_sprite != NULL) && isAlive()) {
        m_renderer->draw(*m_sprite);
    }
}

void Projectile::destroy(void) {
    if (m_sprite != NULL) {
        delete m_sprite;
        m_sprite = NULL;
    }
}

Scene *Projectile::getScene(void) const {
    return static_cast<Scene *const>(m_scene);
}

unsigned int Projectile::getUniqueID(void) const {
    return 0xECF6DBA7;
}

sf::Vector2f Projectile::getScale(void) const {
    return m_scale;
}

void Projectile::setScale(const sf::Vector2f &scale) {
    m_scale = scale;
}

float Projectile::getRotation(void) const {
    sf::Vector2f n = v_normalize(direction);
    return std::atan(n.x / -n.y) * RAD2DEG;
}

void Projectile::setRotation(float rotation) {
    throw std::runtime_error("cannot modify projectile rotation");
}

sf::Vector2f Projectile::getPosition(void) const {
    return m_position;
}

void Projectile::setPosition(const sf::Vector2f &position) {
    throw std::runtime_error("cannot modify projectile position");
}

bool Projectile::isAlive(void) const {
    return v_length(m_position - spawnPosition) < m_range;
}

