#include "alienator.h"

int main(int argc, char **argv) {
    std::srand((unsigned int)(std::time(NULL) & 0xFFFFFFFF));

    Game *game = new GAME_CLASS;
    try {
        sf::Clock clock;
        float dt = 0.0f;

        game->initialize();
        while (game->isRunning()) {
            clock.restart();
            game->update(dt);
            game->render(dt);
            dt = clock.getElapsedTime().asSeconds();

            float target = 1.0f / FPS_CAP;
            if (dt < target) {
                sf::sleep(sf::seconds(target - dt));
            }

            dt = clock.getElapsedTime().asSeconds();
        }
    } catch (const std::exception &e) {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }
    game->destroy();
    delete game;

    return 0;
}

