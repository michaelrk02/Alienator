#pragma once

#include "stdinc.h"
#include "scene.h"

class Alienator;
class Button;

class MainMenuScene : public Scene {
public:
    MainMenuScene(void);
    ~MainMenuScene(void);

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

    UNIQUE_PTR sf::Music *m_menuMus;
    UNIQUE_PTR sf::Texture *m_menuTex;
    UNIQUE_PTR sf::Font *m_largeFnt;

    UNIQUE_PTR sf::RectangleShape *m_background;
    UNIQUE_PTR sf::Text *m_title;
    UNIQUE_PTR Button *m_playBtn;
    UNIQUE_PTR Button *m_armouryBtn;
    UNIQUE_PTR Button *m_quitBtn;
};

