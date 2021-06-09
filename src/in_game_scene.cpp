#include <fstream>
#include <sstream>

#include "alienator.h"
#include "button.h"
#include "human.h"
#include "map.h"

#include "in_game_scene.h"

InGameScene::InGameScene(void) {
    m_gameMus = NULL;
    m_backgroundTex = NULL;
    m_hshipTex = NULL;
    m_hminigunTex = NULL;
    m_hlaserflashFxTex = NULL;
    m_hminigunflashFxTex = NULL;
    m_hlaserProjTex = NULL;
    m_hminigunProjTex = NULL;
    m_largeFnt = NULL;
    m_smallFnt = NULL;
    m_menuclkSnd = NULL;
    m_menunavSnd = NULL;
    m_hlaserWpnSnd = NULL;
    m_hminigunWpnSnd = NULL;

    m_sound = NULL;
    m_background = NULL;
    m_hshipInfoText = NULL;
    m_playerInfoText = NULL;

    m_pausedText = NULL;
    m_pausedResumeBtn = NULL;
    m_pausedAbandonBtn = NULL;

    m_param = NULL;

    m_player = NULL;
}

InGameScene::~InGameScene(void) {
    destroy();
    unloadResources();
}

void InGameScene::create(Alienator *game, sf::RenderTarget *renderer) {
    m_game = game;
    m_renderer = renderer;
}

void InGameScene::initialize(void) {
    if (m_sound == NULL) {
        m_sound = new sf::Sound;
    }

    if (m_background == NULL) {
        m_background = new sf::RectangleShape;
        m_background->setTexture(m_backgroundTex);
    }

    if (m_playerInfoText == NULL) {
        m_playerInfoText = new sf::Text("", *m_smallFnt, 20);
        m_playerInfoText->setFillColor(sf::Color(COLOR_SECONDARY));
    }

    if (m_hshipInfoText == NULL) {
        m_hshipInfoText = new sf::Text("", *m_smallFnt, 20);
        m_hshipInfoText->setFillColor(sf::Color(COLOR_SECONDARY));
    }

    if (m_pausedText == NULL) {
        m_pausedText = new sf::Text("PAUSED", *m_largeFnt, 48);
        m_pausedText->setFillColor(sf::Color(COLOR_PRIMARY));
        m_pausedText->setOutlineColor(sf::Color(COLOR_SECONDARY));
        m_pausedText->setOutlineThickness(4.0f);
    }

    if (m_pausedResumeBtn == NULL) {
        m_pausedResumeBtn = new Button;
        m_pausedResumeBtn->create(this, m_renderer, "RESUME", m_largeFnt, sf::Color(COLOR_PRIMARY), sf::Color(COLOR_SECONDARY), 32);
    }

    if (m_pausedAbandonBtn == NULL) {
        m_pausedAbandonBtn = new Button;
        m_pausedAbandonBtn->create(this, m_renderer, "ABANDON", m_largeFnt, sf::Color(COLOR_PRIMARY), sf::Color(COLOR_SECONDARY), 32);
    }

    if (m_player == NULL) {
        m_player = new Human;
        m_player->create(this, m_renderer, m_hshipTex, m_hminigunTex, m_hlaserflashFxTex, m_hminigunflashFxTex, m_hlaserProjTex, m_hminigunProjTex, m_hlaserWpnSnd, m_hminigunWpnSnd);
    }

    initializeLayout();

    m_gameMus->setLoop(true);
    m_gameMus->play();

    m_paused = false;
}

void InGameScene::update(float dt) {
    sf::Vector2f view = m_renderer->getView().getSize();

    if (m_paused) {
        m_background->setFillColor(sf::Color(0x808080FF));

        m_pausedResumeBtn->update(dt);
        m_pausedAbandonBtn->update(dt);

        if (m_game->hasMouseClicked()) {
            if (m_pausedResumeBtn->isHovered()) {
                m_paused = false;
                m_sound->setBuffer(*m_menuclkSnd);
                m_sound->play();
            } else if (m_pausedAbandonBtn->isHovered()) {
                m_game->setScene(m_game->getScenePointer(SceneID_MainMenu));
            }
        }
    } else {
        m_background->setFillColor(sf::Color(0xFFFFFFFF));

        m_player->update(dt);

        std::ostringstream playerInfo;
        playerInfo << "Level: 1" << std::endl;
        playerInfo << "Experience: 0/500" << std::endl;
        playerInfo << "Credits: $ 0" << std::endl;
        playerInfo << "Map: " << m_param->mapName << std::endl;

        m_playerInfoText->setString(playerInfo.str());

        std::ostringstream hshipInfo;
        hshipInfo << "Hull: 100/100" << std::endl;
        hshipInfo << "Shield: 100/100" << std::endl;
        hshipInfo << "Drones: 5/5" << std::endl;

        m_hshipInfoText->setString(hshipInfo.str());
        m_hshipInfoText->setPosition(8.0f, view.y - m_hshipInfoText->getLocalBounds().height - 8.0f);
    }
}

void InGameScene::render(float dt) {
    m_renderer->draw(*m_background);

    if (m_paused) {
        m_renderer->draw(*m_pausedText);
        m_pausedResumeBtn->render(dt);
        m_pausedAbandonBtn->render(dt);
    } else {
        m_player->render(dt);

        m_renderer->draw(*m_playerInfoText);
        m_renderer->draw(*m_hshipInfoText);
    }
}

void InGameScene::destroy(void) {
    if (m_sound != NULL) {
        delete m_sound;
        m_sound = NULL;
    }
    if (m_background != NULL) {
        delete m_background;
        m_background = NULL;
    }
    if (m_hshipInfoText != NULL) {
        delete m_hshipInfoText;
        m_hshipInfoText = NULL;
    }
    if (m_playerInfoText != NULL) {
        delete m_playerInfoText;
        m_playerInfoText = NULL;
    }

    if (m_pausedText != NULL) {
        delete m_pausedText;
        m_pausedText = NULL;
    }
    if (m_pausedResumeBtn != NULL) {
        delete m_pausedResumeBtn;
        m_pausedResumeBtn = NULL;
    }
    if (m_pausedAbandonBtn != NULL) {
        delete m_pausedAbandonBtn;
        m_pausedAbandonBtn = NULL;
    }

    if (m_param != NULL) {
        InGameParam *param = reinterpret_cast<InGameParam *>(m_param);
        delete param;
        m_param = NULL;
    }

    if (m_player != NULL) {
        delete m_player;
        m_player = NULL;
    }
}

void InGameScene::handle(const sf::Event *event) {
    if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::Key::Escape) {
            if (!m_paused) {
                m_paused = true;
                m_sound->setBuffer(*m_menunavSnd);
                m_sound->play();
            }
        }
    }
    if (event->type == sf::Event::Resized) {
        initializeLayout();
    }
}

void InGameScene::loadResources(void) {
    InGameParam *param = reinterpret_cast<InGameParam *>(m_game->userData);
    if (param == NULL) {
        throw std::runtime_error("invalid in-game parameters");
    }
    m_param = param;

    if (m_gameMus == NULL) {
        std::list<std::string> musicLst;

        std::ifstream musicLstFile(R_LST_MUSIC);
        if (!musicLstFile.is_open()) {
            throw R_LOADERR(R_LST_MUSIC);
        }

        std::string musicName;
        while ((musicLstFile >> musicName).good()) {
            musicLst.push_back(musicName);
        }

        int id = (int)(random_value() * musicLst.size());
        std::list<std::string>::iterator chosen = musicLst.begin();
        std::advance(chosen, id);

        musicLstFile.close();

        m_gameMus = new sf::Music;
        if (!m_gameMus->openFromFile(std::string(R_DIR "music/") + *chosen + ".ogg")) {
            throw std::runtime_error(std::string("unable to load music: ") + *chosen);
        }
    }

    if (m_backgroundTex == NULL) {
        m_backgroundTex = new sf::Texture;
        if (!m_backgroundTex->loadFromFile(std::string(R_DIR "textures/maps/") + m_param->mapName + ".png")) {
            throw std::runtime_error(std::string("unable to load map texture: ") + m_param->mapName);
        }
    }

    if (m_hshipTex == NULL) {
        m_hshipTex = new sf::Texture;
        if (!m_hshipTex->loadFromFile(R_SPR_HSHIP)) {
            throw R_LOADERR(R_SPR_HSHIP);
        }
    }

    if (m_hminigunTex == NULL) {
        m_hminigunTex = new sf::Texture;
        if (!m_hminigunTex->loadFromFile(R_SPR_HMINIGUN)) {
            throw R_LOADERR(R_SPR_HMINIGUN);
        }
    }

    if (m_hlaserflashFxTex == NULL) {
        m_hlaserflashFxTex = new sf::Texture;
        if (!m_hlaserflashFxTex->loadFromFile(R_SPR_FX_HLASERFLASH)) {
            throw R_LOADERR(R_SPR_FX_HLASERFLASH);
        }
    }

    if (m_hminigunflashFxTex == NULL) {
        m_hminigunflashFxTex = new sf::Texture;
        if (!m_hminigunflashFxTex->loadFromFile(R_SPR_FX_HMINIGUNFLASH)) {
            throw R_LOADERR(R_SPR_FX_HMINIGUNFLASH);
        }
    }

    if (m_hlaserProjTex == NULL) {
        m_hlaserProjTex = new sf::Texture;
        if (!m_hlaserProjTex->loadFromFile(R_SPR_PROJ_HLASER)) {
            throw R_LOADERR(R_SPR_PROJ_HLASER);
        }
    }

    if (m_hminigunProjTex == NULL) {
        m_hminigunProjTex = new sf::Texture;
        if (!m_hminigunProjTex->loadFromFile(R_SPR_PROJ_HMINIGUN)) {
            throw R_LOADERR(R_SPR_PROJ_HMINIGUN);
        }
    }

    if (m_largeFnt == NULL) {
        m_largeFnt = new sf::Font;
        if (!m_largeFnt->loadFromFile(R_FNT_LARGE)) {
            throw R_LOADERR(R_FNT_LARGE);
        }
    }

    if (m_smallFnt == NULL) {
        m_smallFnt = new sf::Font;
        if (!m_smallFnt->loadFromFile(R_FNT_SMALL)) {
            throw R_LOADERR(R_FNT_SMALL);
        }
    }

    if (m_menuclkSnd == NULL) {
        m_menuclkSnd = new sf::SoundBuffer;
        if (!m_menuclkSnd->loadFromFile(R_SND_MENUCLK)) {
            throw R_LOADERR(R_SND_MENUCLK);
        }
    }

    if (m_menunavSnd == NULL) {
        m_menunavSnd = new sf::SoundBuffer;
        if (!m_menunavSnd->loadFromFile(R_SND_MENUNAV)) {
            throw R_LOADERR(R_SND_MENUNAV);
        }
    }

    if (m_hlaserWpnSnd == NULL) {
        m_hlaserWpnSnd = new sf::SoundBuffer;
        if (!m_hlaserWpnSnd->loadFromFile(R_SND_WPN_HLASER)) {
            throw R_LOADERR(R_SND_WPN_HLASER);
        }
    }

    if (m_hminigunWpnSnd == NULL) {
        m_hminigunWpnSnd = new sf::SoundBuffer;
        if (!m_hminigunWpnSnd->loadFromFile(R_SND_WPN_HMINIGUN)) {
            throw R_LOADERR(R_SND_WPN_HMINIGUN);
        }
    }
}

void InGameScene::unloadResources(void) {
    if (m_gameMus != NULL) {
        delete m_gameMus;
        m_gameMus = NULL;
    }
    if (m_backgroundTex != NULL) {
        delete m_backgroundTex;
        m_backgroundTex = NULL;
    }
    if (m_hshipTex != NULL) {
        delete m_hshipTex;
        m_hshipTex = NULL;
    }
    if (m_hminigunTex != NULL) {
        delete m_hminigunTex;
        m_hminigunTex = NULL;
    }
    if (m_hlaserflashFxTex != NULL) {
        delete m_hlaserflashFxTex;
        m_hlaserflashFxTex = NULL;
    }
    if (m_hminigunflashFxTex != NULL) {
        delete m_hminigunflashFxTex;
        m_hminigunflashFxTex = NULL;
    }
    if (m_hlaserProjTex != NULL) {
        delete m_hlaserProjTex;
        m_hlaserProjTex = NULL;
    }
    if (m_hminigunProjTex != NULL) {
        delete m_hminigunProjTex;
        m_hminigunProjTex = NULL;
    }
    if (m_largeFnt != NULL) {
        delete m_largeFnt;
        m_largeFnt = NULL;
    }
    if (m_smallFnt != NULL) {
        delete m_smallFnt;
        m_smallFnt = NULL;
    }
    if (m_menuclkSnd != NULL) {
        delete m_menuclkSnd;
        m_menuclkSnd = NULL;
    }
    if (m_menunavSnd != NULL) {
        delete m_menunavSnd;
        m_menunavSnd = NULL;
    }
    if (m_hlaserWpnSnd != NULL) {
        delete m_hlaserWpnSnd;
        m_hlaserWpnSnd = NULL;
    }
    if (m_hminigunWpnSnd != NULL) {
        delete m_hminigunWpnSnd;
        m_hminigunWpnSnd = NULL;
    }
}

GameObject *InGameScene::getGame(void) const {
    return static_cast<GameObject *const>(m_game);
}

void InGameScene::initializeLayout(void) {
    sf::Vector2f view = m_renderer->getView().getSize();

    m_background->setPosition(sf::Vector2f());
    m_background->setSize(view);

    m_playerInfoText->setPosition(8.0f, 8.0f);

    m_pausedText->setPosition(0.5f * (view.x - m_pausedText->getLocalBounds().width), 0.5f * view.y - m_pausedText->getLocalBounds().height - 32.0f);

    m_pausedResumeBtn->update(0.0f);
    m_pausedResumeBtn->setPosition(sf::Vector2f(0.5f * (view.x - m_pausedResumeBtn->getBounds().width), 0.5f * view.y + 16.0f));

    m_pausedResumeBtn->update(0.0f);
    m_pausedAbandonBtn->update(0.0f);
    m_pausedAbandonBtn->setPosition(sf::Vector2f(0.5f * (view.x - m_pausedAbandonBtn->getBounds().width), m_pausedResumeBtn->getBounds().top + m_pausedResumeBtn->getBounds().height + 16.0f));

    m_player->setPosition(sf::Vector2f(0.5f * view.x, 0.5f * view.y));
}

