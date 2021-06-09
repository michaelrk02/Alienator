#include "in_game_scene.h"
#include "weapon.h"

#include "human.h"

Human::Human(void) {
    m_ship = NULL;
    m_minigun = NULL;

    m_laserWpn = NULL;
    m_minigunWpn = NULL;
}

Human::~Human(void) {
    destroy();
}

void Human::create(InGameScene *scene, sf::RenderTarget *renderer, sf::Texture *shipTex, sf::Texture *minigunTex, sf::Texture *laserFlashTex, sf::Texture *minigunFlashTex, sf::Texture *laserProjTex, sf::Texture *minigunProjTex, sf::SoundBuffer *laserSnd, sf::SoundBuffer *minigunSnd) {
    m_scene = scene;
    m_renderer = renderer;
    m_shipTex = shipTex;
    m_minigunTex = minigunTex;
    m_laserFlashTex = laserFlashTex;
    m_minigunFlashTex = minigunFlashTex;
    m_laserProjTex = laserProjTex;
    m_minigunProjTex = minigunProjTex;
    m_laserSnd = laserSnd;
    m_minigunSnd = minigunSnd;

    initialize();
}

void Human::initialize(void) {
    m_radius = 64.0f;
    m_moveSpeed = 150.0f;
    m_rotateSpeed = 90.0f;

    sf::FloatRect shipBounds;
    sf::Vector2f shipScale;

    if (m_ship == NULL) {
        sf::Vector2f target;
        target.x = 2.0f * m_radius;
        target.y = 2.0f * m_radius;

        m_ship = new sf::Sprite(*m_shipTex);

        shipBounds = m_ship->getLocalBounds();
        m_ship->setOrigin(0.5f * shipBounds.width, 0.5f * shipBounds.height);

        shipScale.x = target.x / shipBounds.width;
        shipScale.y = target.y / shipBounds.height;
        m_ship->setScale(shipScale);
    }
    if (m_minigun == NULL) {
        m_minigun = new sf::Sprite(*m_minigunTex);

        sf::FloatRect minigunBounds = m_minigun->getLocalBounds();
        m_minigun->setOrigin(0.5f * minigunBounds.width, 0.5f * minigunBounds.height);
        m_minigun->setScale(shipScale);
    }

    if (m_laserWpn == NULL) {
        m_laserWpn = new Weapon;
        m_laserWpn->create(m_scene, m_renderer, m_laserSnd, m_laserFlashTex, m_laserProjTex, 50.0f, 0.1f, 1000.0f, 1200.0f, 1.0f);
    }
    if (m_minigunWpn == NULL) {
        m_minigunWpn = new Weapon;
        m_minigunWpn->create(m_scene, m_renderer, m_minigunSnd, m_minigunFlashTex, m_minigunProjTex, 500.0f, 0.05f, 500.0f, 600.0f, 0.8f);
    }

    m_shipRotation = 0.0f;
    m_minigunRotation = 0.0f;

    m_position = sf::Vector2f();
}

void Human::update(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        m_shipRotation = (float)m_shipRotation - m_rotateSpeed * dt;
        m_shipRotation = (float)((int)m_shipRotation % 360);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        m_shipRotation = (float)m_shipRotation + m_rotateSpeed * dt;
        m_shipRotation = (float)((int)m_shipRotation % 360);
    }

    m_shipDirection.x = std::sin(m_shipRotation * DEG2RAD);
    m_shipDirection.y = -std::cos(m_shipRotation * DEG2RAD);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        m_position = m_position + m_moveSpeed * m_shipDirection * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        m_position = m_position - m_moveSpeed * m_shipDirection * dt;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        m_minigunRotation = (float)m_minigunRotation - m_rotateSpeed * dt;
        m_minigunRotation = (float)((int)m_minigunRotation % 360);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        m_minigunRotation = (float)m_minigunRotation + m_rotateSpeed * dt;
        m_minigunRotation = (float)((int)m_minigunRotation % 360);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        m_laserWpn->fire();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        m_minigunWpn->fire();
    }

    m_minigunDirection.x = std::sin((m_shipRotation + m_minigunRotation) * DEG2RAD);
    m_minigunDirection.y = -std::cos((m_shipRotation + m_minigunRotation) * DEG2RAD);

    m_ship->setRotation(m_shipRotation);
    m_ship->setPosition(m_position);

    m_minigun->setRotation(m_shipRotation + m_minigunRotation);
    m_minigun->setPosition(m_position);

    m_laserWpn->setRotation(m_shipRotation);
    m_laserWpn->setPosition(m_position + m_radius * m_shipDirection);
    m_laserWpn->update(dt);

    m_minigunWpn->setRotation(m_shipRotation + m_minigunRotation);
    m_minigunWpn->setPosition(m_position + 0.4f * m_radius * m_minigunDirection);
    m_minigunWpn->update(dt);
}

void Human::render(float dt) {
    m_renderer->draw(*m_ship);
    m_renderer->draw(*m_minigun);

    m_laserWpn->render(dt);
    m_minigunWpn->render(dt);
}

void Human::destroy(void) {
    if (m_ship != NULL) {
        delete m_ship;
        m_ship = NULL;
    }
    if (m_minigun != NULL) {
        delete m_minigun;
        m_minigun = NULL;
    }
    if (m_laserWpn != NULL) {
        delete m_laserWpn;
        m_laserWpn = NULL;
    }
    if (m_minigunWpn != NULL) {
        delete m_minigunWpn;
        m_minigunWpn = NULL;
    }
}

Scene *Human::getScene(void) const {
    return static_cast<Scene *const>(m_scene);
}

unsigned int Human::getUniqueID(void) const {
    return 0xD41BBFEB;
}

sf::Vector2f Human::getScale(void) const {
    throw std::runtime_error("cannot modify the object scale");
}

void Human::setScale(const sf::Vector2f &scale) {
    throw std::runtime_error("cannot modify the object scale");
}

float Human::getRotation(void) const {
    return m_shipRotation;
}

void Human::setRotation(float rotation) {
    m_shipRotation = rotation;
}

sf::Vector2f Human::getPosition(void) const {
    return m_position;
}

void Human::setPosition(const sf::Vector2f &position) {
    m_position = position;
}

float Human::getRadius(void) const {
    return m_radius;
}


