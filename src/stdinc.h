#pragma once

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define UNIQUE_PTR
#define SHARED_PTR

#define GAME_CLASS Alienator

#define FPS_CAP 60.0f

#define COLOR_PRIMARY   0xFF0000FF
#define COLOR_SECONDARY 0xFFFF00FF

#define R_DIR           "assets/"
#define R_LOCATE(path)  R_DIR path
#define R_LOADERR(id)   std::runtime_error("Unable to load resource: " id)

#define R_TEX_MENU      R_LOCATE("textures/menu.png")

#define R_FNT_LARGE R_LOCATE("fonts/large.ttf")
#define R_FNT_SMALL R_LOCATE("fonts/small.otf")

#define R_SPR_HMINIGUN  R_LOCATE("sprites/h_minigun.png")
#define R_SPR_HSHIP     R_LOCATE("sprites/h_ship.png")

#define R_SPR_FX_AEXPLODE       R_LOCATE("sprites/effects/a_explode.png")
#define R_SPR_FX_ALASERFLASH    R_LOCATE("sprites/effects/a_laser_flash.png")
#define R_SPR_FX_APLASMAFLASH   R_LOCATE("sprites/effects/a_plasma_flash.png")
#define R_SPR_FX_HEXPLODE       R_LOCATE("sprites/effects/h_explode.png")
#define R_SPR_FX_HLASERFLASH    R_LOCATE("sprites/effects/h_laser_flash.png")
#define R_SPR_FX_HMINIGUNFLASH  R_LOCATE("sprites/effects/h_minigun_flash.png")

#define R_SPR_PAR_ALASER    R_LOCATE("sprites/particles/a_laser.png")
#define R_SPR_PAR_APLASMA   R_LOCATE("sprites/particles/a_plasma.png")
#define R_SPR_PAR_HLASER    R_LOCATE("sprites/particles/h_laser.png")
#define R_SPR_PAR_HMINIGUN  R_LOCATE("sprites/particles/h_minigun.png")
#define R_SPR_PAR_SMOKE     R_LOCATE("sprites/particles/smoke.png")

#define R_SPR_PROJ_ALASER   R_LOCATE("sprites/projectiles/a_laser.png")
#define R_SPR_PROJ_APLASMA  R_LOCATE("sprites/projectiles/a_plasma.png")
#define R_SPR_PROJ_HLASER   R_LOCATE("sprites/projectiles/h_laser.png")
#define R_SPR_PROJ_HMINIGUN R_LOCATE("sprites/projectiles/h_minigun.png")

#define R_SND_MENUCLK   R_LOCATE("sounds/menu_click.ogg")
#define R_SND_MENUERR   R_LOCATE("sounds/menu_error.ogg")
#define R_SND_MENUNAV   R_LOCATE("sounds/menu_navigate.ogg")

#define R_SND_FX_AEXPLODE   R_LOCATE("sounds/effects/a_explode.ogg")
#define R_SND_FX_AHIT       R_LOCATE("sounds/effects/a_hit.ogg")
#define R_SND_FX_HEXPLODE   R_LOCATE("sounds/effects/h_explode.ogg")
#define R_SND_FX_HHIT       R_LOCATE("sounds/effects/h_hit.ogg")
#define R_SND_FX_HSHIELDBRK R_LOCATE("sounds/effects/h_shield_break.ogg")

#define R_SND_WPN_ALASER    R_LOCATE("sounds/weapons/a_laser.ogg")
#define R_SND_WPN_APLASMA   R_LOCATE("sounds/weapons/a_plasma.ogg")
#define R_SND_WPN_HLASER    R_LOCATE("sounds/weapons/h_laser.ogg")
#define R_SND_WPN_HMINIGUN  R_LOCATE("sounds/weapons/h_minigun.ogg")

#define R_MUS_MENU  R_LOCATE("music/menu.ogg")

#define R_LST_MAPS  R_LOCATE("maps.lst")
#define R_LST_MUSIC R_LOCATE("music.lst")

#define DEG2RAD     0.017453f
#define RAD2DEG     57.295780f

inline float random_value(void) {
    float x = (float)std::rand();
    float y = (float)RAND_MAX;
    return x / y;
}

inline float v_length(const sf::Vector2f &v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

inline sf::Vector2f v_normalize(const sf::Vector2f &v) {
    return (1.0f / v_length(v)) * v;
}

