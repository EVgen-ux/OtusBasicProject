#include "Map.h"

#include <SFML/Graphics.hpp>

// Определение статического члена TileMap
std::string Map::TileMap[Map::H] = {
    // NOLINT

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
    "B        B               A            EB",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};
void Map::draw(sf::RenderWindow &window, float offsetX, float offsetY) {
  sf::RectangleShape rectangle;
  // const int TileSize = 32;
  rectangle.setSize(sf::Vector2f(TileSize, TileSize)); // Размер блока

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (TileMap[i][j] == 'B')
        rectangle.setFillColor(sf::Color::Black);
      if (TileMap[i][j] == 'E')
        rectangle.setFillColor(sf::Color::Green);
      if (TileMap[i][j] == 'A')
        rectangle.setFillColor(sf::Color::Red);
      if (TileMap[i][j] == ' ')
        continue;

      rectangle.setPosition(j * TileSize - offsetX, i * TileSize - offsetY);
      window.draw(rectangle);
    }
  }
}