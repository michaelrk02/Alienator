#include "muzzle_flash_effect.h"

MuzzleFlashEffect::MuzzleFlashEffect(void) {
}

MuzzleFlashEffect::~MuzzleFlashEffect(void) {
}

void MuzzleFlashEffect::initialize(void) {
    Effect::initialize();

    sf::FloatRect bounds = m_sprite->getLocalBounds();
    m_sprite->setOrigin(0.5f * bounds.width, bounds.height);
}

