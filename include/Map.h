#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <string>

class Map {
public:
  static const int H = 12; // Высота карты
  static const int W = 40; // Ширина карты
  static std::string TileMap[H];
  static const int TileSize = 32; // Размер тайла
  static void draw(sf::RenderWindow &window, float offsetX, float offsetY);
};

#endif // MAP_H