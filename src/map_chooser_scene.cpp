#include <cstring>
#include <fstream>
#include <sstream>

#include "alienator.h"
#include "button.h"

#include "map_chooser_scene.h"

MapChooserScene::MapChooserScene(void) {
    m_game = NULL;
    m_renderer = NULL;

    m_menuMus = NULL;
    m_menuTex = NULL;
    m_largeFnt = NULL;
    m_smallFnt = NULL;
    m_menunavSnd = NULL;
    m_menuerrSnd = NULL;

    m_background = NULL;
    m_backBtn = NULL;
    m_prevBtn = NULL;
    m_nextBtn = NULL;
    m_launchBtn = NULL;
    m_sound = NULL;

    m_selectedOverviewTex = NULL;
    m_selectedOverview = NULL;
    m_selectedDescription = NULL;
}

MapChooserScene::~MapChooserScene(void) {
    destroy();
    unloadResources();
}

void MapChooserScene::create(Alienator *game, sf::RenderTarget *renderer) {
    m_game = game;
    m_renderer = renderer;
}

void MapChooserScene::initialize(void) {
    if (m_background == NULL) {
        m_background = new sf::RectangleShape;
        m_background->setTexture(m_menuTex);
    }

    if (m_backBtn == NULL) {
        m_backBtn = new Button;
        m_backBtn->create(this, m_renderer, "BACK", m_largeFnt, sf::Color(COLOR_PRIMARY), sf::Color(COLOR_SECONDARY), 32);
    }

    if (m_prevBtn == NULL) {
        m_prevBtn = new Button;
        m_prevBtn->create(this, m_renderer, "< PREV", m_largeFnt, sf::Color(COLOR_PRIMARY), sf::Color(COLOR_SECONDARY), 24);
    }

    if (m_nextBtn == NULL) {
        m_nextBtn = new Button;
        m_nextBtn->create(this, m_renderer, "NEXT >", m_largeFnt, sf::Color(COLOR_PRIMARY), sf::Color(COLOR_SECONDARY), 24);
    }

    if (m_launchBtn == NULL) {
        m_launchBtn = new Button;
        m_launchBtn->create(this, m_renderer, "LAUNCH!", m_largeFnt, sf::Color(COLOR_PRIMARY), sf::Color(COLOR_SECONDARY), 32);
    }

    if (m_sound == NULL) {
        m_sound = new sf::Sound;
    }

    m_menuMus->setLoop(true);
    m_menuMus->play();

    m_selected = m_maps.begin();

    refresh();
    initializeLayout();
}

void MapChooserScene::update(float dt) {
    m_backBtn->update(dt);
    m_prevBtn->update(dt);
    m_nextBtn->update(dt);
    m_launchBtn->update(dt);

    if (m_game->hasMouseClicked()) {
        if (m_backBtn->isHovered()) {
            m_game->setScene(m_game->getScenePointer(SceneID_MainMenu));
        } else if (m_prevBtn->isHovered()) {
            if (m_selected != m_maps.begin()) {
                --m_selected;
                refresh();
                m_sound->setBuffer(*m_menunavSnd);
            } else {
                m_sound->setBuffer(*m_menuerrSnd);
            }
            m_sound->play();
        } else if (m_nextBtn->isHovered()) {
            if (m_selected != --m_maps.end()) {
                ++m_selected;
                refresh();
                m_sound->setBuffer(*m_menunavSnd);
            } else {
                m_sound->setBuffer(*m_menuerrSnd);
            }
            m_sound->play();
        } else if (m_launchBtn->isHovered()) {
            InGameParam *param = new InGameParam;
            strncpy(param->mapName, (*m_selected).c_str(), 50);
            param->mapInfo = m_selectedInfo;

            m_game->userData = reinterpret_cast<void *>(param);
            m_game->setScene(m_game->getScenePointer(SceneID_InGame));
        }
    }
}

void MapChooserScene::render(float dt) {
    m_renderer->draw(*m_background);

    m_backBtn->render(dt);
    m_prevBtn->render(dt);
    m_nextBtn->render(dt);
    m_launchBtn->render(dt);

    m_renderer->draw(*m_selectedOverview);
    m_renderer->draw(*m_selectedDescription);
}

void MapChooserScene::destroy(void) {
    if (m_selectedOverview != NULL) {
        delete m_selectedOverview;
        m_selectedOverview = NULL;
    }
    if (m_selectedDescription != NULL) {
        delete m_selectedDescription;
        m_selectedDescription = NULL;
    }
    if (m_selectedOverviewTex != NULL) {
        delete m_selectedOverviewTex;
        m_selectedOverviewTex = NULL;
    }

    if (m_background != NULL) {
        delete m_background;
        m_background = NULL;
    }
    if (m_backBtn != NULL) {
        delete m_backBtn;
        m_backBtn = NULL;
    }
    if (m_prevBtn != NULL) {
        delete m_prevBtn;
        m_prevBtn = NULL;
    }
    if (m_nextBtn != NULL) {
        delete m_nextBtn;
        m_nextBtn = NULL;
    }
    if (m_launchBtn != NULL) {
        delete m_launchBtn;
        m_launchBtn = NULL;
    }
}

void MapChooserScene::handle(const sf::Event *event) {
    if (event->type == sf::Event::Resized) {
        initializeLayout();
    }
}

void MapChooserScene::loadResources(void) {
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

    if (m_smallFnt == NULL) {
        m_smallFnt = new sf::Font;
        if (!m_smallFnt->loadFromFile(R_FNT_SMALL)) {
            throw R_LOADERR(R_FNT_SMALL);
        }
    }

    if (m_menunavSnd == NULL) {
        m_menunavSnd = new sf::SoundBuffer;
        if (!m_menunavSnd->loadFromFile(R_SND_MENUNAV)) {
            throw R_LOADERR(R_SND_MENUNAV);
        }
    }

    if (m_menuerrSnd == NULL) {
        m_menuerrSnd = new sf::SoundBuffer;
        if (!m_menuerrSnd->loadFromFile(R_SND_MENUERR)) {
            throw R_LOADERR(R_SND_MENUERR);
        }
    }

    m_maps.clear();
    std::ifstream mapsLst(R_LST_MAPS);
    if (!mapsLst.is_open()) {
        throw R_LOADERR(R_LST_MAPS);
    }
    std::string mapName;
    while ((mapsLst >> mapName).good()) {
        m_maps.push_back(mapName);
    }
    mapsLst.close();
}

void MapChooserScene::unloadResources(void) {
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
    if (m_smallFnt != NULL) {
        delete m_smallFnt;
        m_smallFnt = NULL;
    }
    if (m_sound != NULL) {
        delete m_sound;
        m_sound = NULL;
    }
}

GameObject *MapChooserScene::getGame(void) const {
    return static_cast<GameObject *const>(m_game);
}

void MapChooserScene::initializeLayout(void) {
    sf::Vector2f view = m_renderer->getView().getSize();

    m_background->setPosition(sf::Vector2f());
    m_background->setSize(view);

    m_backBtn->setPosition(sf::Vector2f(8.0f, 8.0f));

    m_prevBtn->update(0.0f);
    m_prevBtn->setPosition(sf::Vector2f(8.0f, 0.5f * (view.y - m_prevBtn->getBounds().height)));

    m_nextBtn->update(0.0f);
    m_nextBtn->setPosition(sf::Vector2f(view.x - 8.0f - m_nextBtn->getBounds().width, 0.5f * (view.y - m_nextBtn->getBounds().height)));

    m_launchBtn->update(0.0f);
    m_launchBtn->setPosition(sf::Vector2f(0.5f * (view.x - m_launchBtn->getBounds().width), view.y - 8.0f - m_launchBtn->getBounds().height));

    sf::Vector2f overviewSize = sf::Vector2f(0.5f * view.x, 0.5f * view.y);
    m_selectedOverview->setPosition(0.5f * (view.x - overviewSize.x), 96.0f);
    m_selectedOverview->setSize(overviewSize);

    sf::FloatRect overviewBounds = m_selectedOverview->getGlobalBounds();
    m_selectedDescription->setPosition(overviewBounds.left, overviewBounds.top + overviewBounds.height + 16.0f);
}

void MapChooserScene::refresh(void) {
    if (m_selectedOverview != NULL) {
        delete m_selectedOverview;
    }
    if (m_selectedDescription != NULL) {
        delete m_selectedDescription;
    }
    if (m_selectedOverviewTex != NULL) {
        delete m_selectedOverviewTex;
    }

    std::string mapName = *m_selected;

    std::string mapFile = std::string(R_DIR "maps/") + mapName + ".map";
    std::ifstream mapStream(mapFile.c_str(), std::ios::binary);
    if (!mapStream.is_open()) {
        throw std::runtime_error(std::string("failed loading map file: ") + mapName);
    }

    MapInfo map;
    mapStream.read(reinterpret_cast<char *>(&map.fourcc), sizeof(unsigned int));
    if (map.fourcc != FOURCC_MAP) {
        throw std::runtime_error(std::string("invalid map file: ") + mapName);
    }
    mapStream.seekg(0);
    mapStream.read(reinterpret_cast<char *>(&map), sizeof(MapInfo));
    mapStream.close();
    m_selectedInfo = map;

    std::string mapOverviewTexFile = std::string(R_DIR "textures/maps/") + mapName + ".png";
    m_selectedOverviewTex = new sf::Texture;
    if (!m_selectedOverviewTex->loadFromFile(mapOverviewTexFile)) {
        throw std::runtime_error(std::string("failed loading map texture: ") + mapName);
    }

    m_selectedOverview = new sf::RectangleShape;
    m_selectedOverview->setOutlineThickness(4.0f);
    m_selectedOverview->setOutlineColor(sf::Color(COLOR_SECONDARY));
    m_selectedOverview->setTexture(m_selectedOverviewTex);

    std::ostringstream description;
    description.precision(2);
    description.setf(std::ios::fixed, std::ios::floatfield);
    description << "Map: " << mapName << std::endl;
    description << "Alien health factor: " << map.alienHealthFactor << std::endl;
    description << "Alien speed factor: " << map.alienSpeedFactor << std::endl;
    description << "Alien strength factor: " << map.alienStrengthFactor << std::endl;

    m_selectedDescription = new sf::Text(description.str(), *m_smallFnt, 20);
    m_selectedDescription->setFillColor(sf::Color(COLOR_SECONDARY));

    initializeLayout();
}


