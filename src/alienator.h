#pragma once

#include "stdinc.h"
#include "map.h"
#include "game.h"

class Scene;
class MainMenuScene;
class ArmouryScene;
class MapChooserScene;
class InGameScene;

enum SceneID {
    SceneID_MainMenu,
    SceneID_Armoury,
    SceneID_MapChooser,
    SceneID_InGame
};

struct InGameParam {
    char mapName[50];
    MapInfo mapInfo;
};

class Alienator : public Game {
public:
    Alienator(void);
    ~Alienator(void);

    void initialize(void);
    void update(float dt);
    void render(float dt);
    void destroy(void);

    bool isRunning(void) const;
    void setRunning(bool running);

    Scene *getScene(void) const;
    void setScene(Scene *scene);

    sf::Vector2f getMouseLocation(void) const;
    bool hasMouseClicked(void) const;
    bool hasMouseReleased(void) const;

    Scene *getScenePointer(SceneID id) const;

    SHARED_PTR void *userData;

protected:
    bool m_running;

    UNIQUE_PTR sf::RenderWindow *m_window;
    SHARED_PTR Scene *m_scene;
    SHARED_PTR Scene *m_sceneBuffer;

    UNIQUE_PTR MainMenuScene *m_mainMenuScene;
    UNIQUE_PTR ArmouryScene *m_armouryScene;
    UNIQUE_PTR MapChooserScene *m_mapChooserScene;
    UNIQUE_PTR InGameScene *m_inGameScene;

    bool m_lastMouseClick;
};

