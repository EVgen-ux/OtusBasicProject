#include "Map.h"

#include <SFML/Graphics.hpp>

// Определение статического члена TileMap
std::string Map::TileMap[Map::H] = {
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B                                      B",
    "B          BB                          B",
    "B         B  BB                       EB",
    "B        B                            EB",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};
#include <stdexcept>
void Map::draw(sf::RenderWindow &window, float offsetX, float offsetY) {
  sf::RectangleShape rectangle;
  rectangle.setSize(sf::Vector2f(32, 32));  // Размер блока

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (TileMap[i][j] == 'B') rectangle.setFillColor(sf::Color::Black);
      if (TileMap[i][j] == 'E') rectangle.setFillColor(sf::Color::Green);
      if (TileMap[i][j] == ' ') continue;

      rectangle.setPosition(j * 32 - offsetX, i * 32 - offsetY);
      window.draw(rectangle);
    }
  }
}