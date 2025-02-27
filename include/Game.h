#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Map.h"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    Player player;
    sf::Texture playerTexture;
    sf::Font font;
    sf::Text winText;
    bool gameOver;
    float offsetX, offsetY;

    void handleEvents();
    void update(float time);
    void render();
};

#endif // GAME_H