#include "in_game_scene.h"
#include "muzzle_flash_effect.h"
#include "projectile.h"

#include "weapon.h"

Weapon::Weapon(void) {
    m_sound = NULL;
    m_muzzleFlash = NULL;
}

Weapon::~Weapon(void) {
    destroy();
}

void Weapon::create(InGameScene *scene, sf::RenderTarget *renderer, sf::SoundBuffer *fireSnd, sf::Texture *muzzleFlashFxTex, sf::Texture *projectileTex, float fireRate, float muzzleFlashLifetime, float projectileSpeed, float projectileRange, float accuracy) {
    m_scene = scene;
    m_renderer = renderer;
    m_fireSnd = fireSnd;
    m_muzzleFlashFxTex = muzzleFlashFxTex;
    m_projectileTex = projectileTex;
    m_fireRate = fireRate;
    m_muzzleFlashLifetime = muzzleFlashLifetime;
    m_projectileSpeed = projectileSpeed;
    m_projectileRange = projectileRange;
    m_accuracy = accuracy;

    initialize();
}

void Weapon::initialize(void) {
    if (m_sound == NULL) {
        m_sound = new sf::Sound;
    }

    if (m_muzzleFlash == NULL) {
        m_muzzleFlash = new MuzzleFlashEffect;
        m_muzzleFlash->create(m_scene, m_renderer, m_muzzleFlashFxTex, m_muzzleFlashLifetime);
    }
}

void Weapon::update(float dt) {
    m_muzzleFlash->setRotation(m_rotation);
    m_muzzleFlash->setPosition(m_position);

    m_muzzleFlash->update(dt);

    for (std::list<UNIQUE_PTR Projectile *>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); ) {
        Projectile *proj = *it;
        if (proj->isAlive()) {
            proj->update(dt);
            ++it;
        } else {
            delete proj;
            it = m_projectiles.erase(it);
        }
    }
}

void Weapon::render(float dt) {
    m_muzzleFlash->render(dt);

    for (std::list<UNIQUE_PTR Projectile *>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); ++it) {
        (*it)->render(dt);
    }
}

void Weapon::destroy(void) {
    if (m_sound != NULL) {
        delete m_sound;
        m_sound = NULL;
    }
    if (m_muzzleFlash != NULL) {
        delete m_muzzleFlash;
        m_muzzleFlash = NULL;
    }
}

Scene *Weapon::getScene(void) const {
    return static_cast<Scene *const>(m_scene);
}

unsigned int Weapon::getUniqueID(void) const {
    return 0xBA555DFD;
}

sf::Vector2f Weapon::getScale(void) const {
    throw std::runtime_error("cannot get/set weapon scale");
}

void Weapon::setScale(const sf::Vector2f &scale) {
    throw std::runtime_error("cannot get/set weapon scale");
}

float Weapon::getRotation(void) const {
    return m_rotation;
}

void Weapon::setRotation(float rotation) {
    m_rotation = rotation;
}

sf::Vector2f Weapon::getPosition(void) const {
    return m_position;
}

void Weapon::setPosition(const sf::Vector2f &position) {
    m_position = position;
}

bool Weapon::canFire(void) {
    float fireDelay = 60.0f / m_fireRate;
    return m_fireClock.getElapsedTime().asSeconds() > fireDelay;
}

void Weapon::fire(void) {
    if (canFire()) {
        m_fireClock.restart();
        m_muzzleFlash->initialize();
        m_sound->setBuffer(*m_fireSnd);
        m_sound->play();

        Projectile *proj = new Projectile;
        proj->create(m_scene, m_renderer, m_projectileTex, m_projectileRange);
        proj->spawnPosition = m_position;

        float projRotation = m_rotation + (-1.0f + 2.0f * random_value()) * (1.0f - m_accuracy) * 60.0f;

        proj->direction.x = std::sin(projRotation * DEG2RAD);
        proj->direction.y = -std::cos(projRotation * DEG2RAD);
        proj->speed = m_projectileSpeed;
        proj->initialize();
        m_projectiles.push_back(proj);
    }
}


