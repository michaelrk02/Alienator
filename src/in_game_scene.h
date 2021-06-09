#pragma once

#include <list>

#include "stdinc.h"
#include "scene.h"

class Alien;
class Alienator;
class Button;
class Human;

struct InGameParam;

class InGameScene : public Scene {
public:
    InGameScene(void);
    ~InGameScene(void);

    void create(Alienator *game, sf::RenderTarget *renderer);

    void initialize(void);
    void update(float dt);
    void render(float dt);
    void destroy(void);

    void handle(const sf::Event *event);

    void loadResources(void);
    void unloadResources(void);

    GameObject *getGame(void) const;

protected:
    void initializeLayout(void);

    SHARED_PTR Alienator *m_game;
    SHARED_PTR sf::RenderTarget *m_renderer;

    UNIQUE_PTR sf::Music *m_gameMus;
    UNIQUE_PTR sf::Texture *m_backgroundTex;
    UNIQUE_PTR sf::Texture *m_hshipTex;
    UNIQUE_PTR sf::Texture *m_hminigunTex;
    UNIQUE_PTR sf::Texture *m_hlaserflashFxTex;
    UNIQUE_PTR sf::Texture *m_hminigunflashFxTex;
    UNIQUE_PTR sf::Texture *m_hlaserProjTex;
    UNIQUE_PTR sf::Texture *m_hminigunProjTex;
    UNIQUE_PTR sf::Font *m_largeFnt;
    UNIQUE_PTR sf::Font *m_smallFnt;
    UNIQUE_PTR sf::SoundBuffer *m_menuclkSnd;
    UNIQUE_PTR sf::SoundBuffer *m_menunavSnd;
    UNIQUE_PTR sf::SoundBuffer *m_hlaserWpnSnd;
    UNIQUE_PTR sf::SoundBuffer *m_hminigunWpnSnd;

    UNIQUE_PTR sf::Sound *m_sound;
    UNIQUE_PTR sf::RectangleShape *m_background;
    UNIQUE_PTR sf::Text *m_playerInfoText;
    UNIQUE_PTR sf::Text *m_hshipInfoText;

    bool m_paused;
    UNIQUE_PTR sf::Text *m_pausedText;
    UNIQUE_PTR Button *m_pausedResumeBtn;
    UNIQUE_PTR Button *m_pausedAbandonBtn;

    UNIQUE_PTR InGameParam *m_param;

    UNIQUE_PTR Human *m_player;
    std::list<UNIQUE_PTR Alien *> m_enemies;
};

