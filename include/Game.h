#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Player.h"

// Шаблонная функция для отрисовки объектов
template <typename T>
void drawObject(sf::RenderWindow &window, T &object, float offsetX,
                float offsetY) {
  object.draw(window, offsetX, offsetY);
}

class Game {
public:
  Game();
  void run();
  void handleEvents();
  void update(float time);
  void render();

private:
  sf::RenderWindow window;
  Player player;
  sf::Texture playerTexture;
  sf::Font font;
  sf::Text winText;
  sf::Text loseText;
  bool gameOver;
  float offsetX, offsetY;
};

#endif // GAME_H
