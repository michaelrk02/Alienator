#pragma once

#include <list>

#include "stdinc.h"
#include "map.h"
#include "scene.h"

class Alienator;
class Button;

class MapChooserScene : public Scene {
public:
    MapChooserScene(void);
    ~MapChooserScene(void);

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
    void refresh(void);

    SHARED_PTR Alienator *m_game;
    SHARED_PTR sf::RenderTarget *m_renderer;

    UNIQUE_PTR sf::Music *m_menuMus;
    UNIQUE_PTR sf::Texture *m_menuTex;
    UNIQUE_PTR sf::Font *m_largeFnt;
    UNIQUE_PTR sf::Font *m_smallFnt;
    UNIQUE_PTR sf::SoundBuffer *m_menunavSnd;
    UNIQUE_PTR sf::SoundBuffer *m_menuerrSnd;

    UNIQUE_PTR sf::RectangleShape *m_background;
    UNIQUE_PTR Button *m_backBtn;
    UNIQUE_PTR Button *m_prevBtn;
    UNIQUE_PTR Button *m_nextBtn;
    UNIQUE_PTR Button *m_launchBtn;
    UNIQUE_PTR sf::Sound *m_sound;

    std::list<std::string> m_maps;
    std::list<std::string>::iterator m_selected;
    UNIQUE_PTR sf::Texture *m_selectedOverviewTex;
    UNIQUE_PTR sf::RectangleShape *m_selectedOverview;
    UNIQUE_PTR sf::Text *m_selectedDescription;
    MapInfo m_selectedInfo;
};

