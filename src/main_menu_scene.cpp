#include "alienator.h"
#include "button.h"

#include "main_menu_scene.h"

MainMenuScene::MainMenuScene(void) {
    m_menuMus = NULL;
    m_menuTex = NULL;
    m_largeFnt = NULL;

    m_background = NULL;
    m_title = NULL;
    m_playBtn = NULL;
    m_armouryBtn = NULL;
    m_quitBtn = NULL;
}

MainMenuScene::~MainMenuScene(void) {
    destroy();
    unloadResources();
}

void MainMenuScene::create(Alienator *game, sf::RenderTarget *renderer) {
    m_game = game;
    m_renderer = renderer;
}

void MainMenuScene::initialize(void) {
    if (m_background == NULL) {
        m_background = new sf::RectangleShape;
        m_background->setTexture(m_menuTex);
    }

    if (m_title == NULL) {
        m_title = new sf::Text("ALIENATOR", *m_largeFnt, 48);
        m_title->setFillColor(sf::Color(COLOR_PRIMARY));
        m_title->setOutlineColor(sf::Color(COLOR_SECONDARY));
        m_title->setOutlineThickness(4);
    }

    if (m_playBtn == NULL) {
        m_playBtn = new Button;
        m_playBtn->create(this, m_renderer, "PLAY", m_largeFnt, sf::Color(COLOR_PRIMARY), sf::Color(COLOR_SECONDARY), 32);
    }

    if (m_armouryBtn == NULL) {
        m_armouryBtn = new Button;
        m_armouryBtn->create(this, m_renderer, "ARMOURY", m_largeFnt, sf::Color(COLOR_PRIMARY), sf::Color(COLOR_SECONDARY), 32);
    }

    if (m_quitBtn == NULL) {
        m_quitBtn = new Button;
        m_quitBtn->create(this, m_renderer, "QUIT", m_largeFnt, sf::Color(COLOR_PRIMARY), sf::Color(COLOR_SECONDARY), 32);
    }

    m_menuMus->setLoop(true);
    m_menuMus->play();

    initializeLayout();
}

void MainMenuScene::update(float dt) {
    m_playBtn->update(dt);
    m_armouryBtn->update(dt);
    m_quitBtn->update(dt);

    if (m_game->hasMouseClicked()) {
        if (m_playBtn->isHovered()) {
            m_game->setScene(m_game->getScenePointer(SceneID_MapChooser));
        } else if (m_armouryBtn->isHovered()) {
            std::cout << "Going to armoury" << std::endl;
        } else if (m_quitBtn->isHovered()) {
            m_game->setRunning(false);
        }
    }
}

void MainMenuScene::render(float dt) {
    m_renderer->draw(*m_background);
    m_renderer->draw(*m_title);
    m_playBtn->render(dt);
    m_armouryBtn->render(dt);
    m_quitBtn->render(dt);
}

void MainMenuScene::destroy(void) {
    if (m_background != NULL) {
        delete m_background;
        m_background = NULL;
    }
    if (m_title != NULL) {
        delete m_title;
        m_title = NULL;
    }
    if (m_playBtn != NULL) {
        delete m_playBtn;
        m_playBtn = NULL;
    }
    if (m_armouryBtn != NULL) {
        delete m_armouryBtn;
        m_armouryBtn = NULL;
    }
    if (m_quitBtn != NULL) {
        delete m_quitBtn;
        m_quitBtn = NULL;
    }
}

void MainMenuScene::handle(const sf::Event *event) {
    if (event->type == sf::Event::Resized) {
        initializeLayout();
    }
}

void MainMenuScene::loadResources(void) {
    if (m_menuMus == NULL) {
        m_menuMus = new sf::Music;
        if (!m_menuMus->openFromFile(R_MUS_MENU)) {
            throw R_LOADERR(R_MUS_MENU);
        }
    }

    if (m_menuTex == NULL) {
        m_menuTex = new sf::Texture;
        if (!m_menuTex->loadFromFile(R_TEX_MENU)) {
            throw R_LOADERR(R_TEX_MENU);
        }
    }

    if (m_largeFnt == NULL) {
        m_largeFnt = new sf::Font;
        if (!m_largeFnt->loadFromFile(R_FNT_LARGE)) {
            throw R_LOADERR(R_FNT_LARGE);
        }
    }
}

void MainMenuScene::unloadResources(void) {
    if (m_menuMus != NULL) {
        delete m_menuMus;
        m_menuMus = NULL;
    }
    if (m_menuTex != NULL) {
        delete m_menuTex;
        m_menuTex = NULL;
    }
    if (m_largeFnt != NULL) {
        delete m_largeFnt;
        m_largeFnt = NULL;
    }
}

GameObject *MainMenuScene::getGame(void) const {
    return static_cast<GameObject *const>(m_game);
}

void MainMenuScene::initializeLayout(void) {
    sf::Vector2f view = m_renderer->getView().getSize();

    m_background->setPosition(sf::Vector2f());
    m_background->setSize(view);

    m_title->setPosition(view.x - m_title->getLocalBounds().width - 8.0f, 0.0f);
    m_playBtn->setPosition(sf::Vector2f(0.78f * view.x, 0.26f * view.y));
    m_armouryBtn->setPosition(sf::Vector2f(0.5f * view.x, 0.67f * view.y));
    m_quitBtn->setPosition(sf::Vector2f(0.24f * view.x, 0.39 * view.y));

}

