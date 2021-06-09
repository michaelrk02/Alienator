#include "in_game_scene.h"
#include "main_menu_scene.h"
#include "map_chooser_scene.h"
#include "scene.h"

#include "alienator.h"

Alienator::Alienator(void) {
    userData = NULL;

    m_window = NULL;
    m_scene = NULL;
    m_sceneBuffer = NULL;

    m_mainMenuScene = NULL;
    m_armouryScene = NULL;
    m_mapChooserScene = NULL;
    m_inGameScene = NULL;
}

Alienator::~Alienator(void) {
    destroy();
}

void Alienator::initialize(void) {
    m_running = true;

    if (m_window == NULL) {
        m_window = new sf::RenderWindow(sf::VideoMode(1024, 768), "Alienator");
    }

    if (m_mainMenuScene == NULL) {
        m_mainMenuScene = new MainMenuScene;
        m_mainMenuScene->create(this, m_window);
    }

    if (m_mapChooserScene == NULL) {
        m_mapChooserScene = new MapChooserScene;
        m_mapChooserScene->create(this, m_window);
    }

    if (m_inGameScene == NULL) {
        m_inGameScene = new InGameScene;
        m_inGameScene->create(this, m_window);
    }

    m_lastMouseClick = false;

    setScene(m_mainMenuScene);
}

void Alienator::update(float dt) {
    if ((m_sceneBuffer != NULL) && (m_scene != m_sceneBuffer)) {
        if (m_scene != NULL) {
            m_scene->destroy();
            m_scene->unloadResources();
        }
        m_scene = m_sceneBuffer;
        if (m_scene != NULL) {
            m_scene->loadResources();
            m_scene->initialize();
        }
        m_sceneBuffer = NULL;
    }

    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_running = false;
        }
        if (event.type == sf::Event::Resized) {
            sf::FloatRect area(0, 0, event.size.width, event.size.height);
            m_window->setView(sf::View(area));
        }
        if (m_scene != NULL) {
            m_scene->handle(&event);
        }
    }

    if (m_scene != NULL) {
        m_scene->update(dt);
    }

    m_lastMouseClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Alienator::render(float dt) {
    m_window->clear(sf::Color(40, 40, 100, 255));

    if (m_scene != NULL) {
        m_scene->render(dt);
    }

    m_window->display();
}

void Alienator::destroy(void) {
    if (m_mainMenuScene != NULL) {
        delete m_mainMenuScene;
        m_mainMenuScene = NULL;
    }

    if (m_mapChooserScene != NULL) {
        delete m_mapChooserScene;
        m_mapChooserScene = NULL;
    }

    if (m_inGameScene != NULL) {
        delete m_inGameScene;
        m_inGameScene = NULL;
    }

    if (m_window != NULL) {
        delete m_window;
        m_window = NULL;
    }
}

bool Alienator::isRunning(void) const {
    return m_running;
}

void Alienator::setRunning(bool running) {
    m_running = running;
}

Scene *Alienator::getScene(void) const {
    return m_scene;
}

void Alienator::setScene(Scene *scene) {
    m_sceneBuffer = scene;
}

sf::Vector2f Alienator::getMouseLocation(void) const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
    sf::Vector2f mouseLoc = m_window->mapPixelToCoords(mousePos);
    return mouseLoc;
}

bool Alienator::hasMouseClicked(void) const {
    return sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_lastMouseClick;
}

bool Alienator::hasMouseReleased(void) const {
    return !sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_lastMouseClick;
}

Scene *Alienator::getScenePointer(SceneID id) const {
    Scene *scene = NULL;

    switch (id) {
    case SceneID_MainMenu:
        scene = static_cast<Scene *const>(m_mainMenuScene);
        break;
    case SceneID_Armoury:
        scene = reinterpret_cast<Scene *const>(m_armouryScene);
        break;
    case SceneID_MapChooser:
        scene = static_cast<Scene *const>(m_mapChooserScene);
        break;
    case SceneID_InGame:
        scene = static_cast<Scene *const>(m_inGameScene);
        break;
    }

    return scene;
}

