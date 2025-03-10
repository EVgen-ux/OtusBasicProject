#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
  float dx, dy;
  sf::FloatRect rect;
  bool onGround;
  sf::Sprite sprite;
  float curFrame;
  bool win;
  int tileFramewidth = 47, tileFrameHeight = 90, tileFrame_dx = 45,
      tileFrame_dy = 60;

  Player(sf::Texture &image);
  void update(float time, float &offsetX, float &offsetY);
  void Collision(char axis, const std::string TileMap[], int H, int W);

  // Добавляем метод draw
  void draw(sf::RenderWindow &window, float offsetX, float offsetY) {
    sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
    window.draw(sprite);
  }
};

#endif // PLAYER_H
