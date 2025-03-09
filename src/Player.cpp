#include "Player.h"

#include <cmath>

#include "Map.h"  // Подключаем заголовочный файл Map.h

Player::Player(sf::Texture &image) {
  sprite.setTexture(image);
  sprite.setTextureRect(sf::IntRect(tileFramewidth, tileFrameHeight, tileFrame_dx, tileFrame_dy));
  rect = sf::FloatRect(100, 150, 45, 60); //NOLINT // Начальная позиция на земле
  dx = dy = 0;
  curFrame = 0;
  onGround = true;  // Персонаж на земле в начале игры
  win = false;
}

// Конструктор
// Player::Player(sf::Texture &image)
//     : dx(0),                // Инициализация dx
//       dy(0),                // Инициализация dy
//       rect(100, 210 - 60, 45, 60),  // Инициализация rect
//       onGround(true),       // Инициализация onGround
//       sprite(),             // Инициализация sprite
//       curFrame(0),          // Инициализация curFrame
//       win(false) {          // Инициализация win
//   // Установка текстуры и текстуры спрайта
//   sprite.setTexture(image);
//   sprite.setTextureRect(sf::IntRect(47, 90, 45, 60));
// }


void Player::update(float time, float &offsetX, float &offsetY) {
  if (win) {
    return;
  }  // Если игра завершена, не обновлять состояние игрока

  rect.left += dx * time;
  Collision('x', Map::TileMap, Map::H, Map::W);  // Используем статические члены Map

  if (!onGround) dy = dy + 0.002 * time; // NOLINT
  rect.top += dy * time;
  onGround = false;

  Collision('y', Map::TileMap, Map::H, Map::W);  // Используем статические члены Map

  curFrame += static_cast<float>(0.005 * time);
  if (curFrame > 3) {
    curFrame -= 3;
  }

  if (dx > 0) {
    sprite.setTextureRect(sf::IntRect(tileFramewidth * static_cast<int>(curFrame), tileFrameHeight, tileFrame_dx, tileFrame_dy));
  }
  if (dx < 0) {
    sprite.setTextureRect(sf::IntRect(tileFramewidth * (static_cast<int>(curFrame) + 1), tileFrameHeight, -tileFrame_dx, tileFrame_dy));
  }
  sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
  dx = 0;
}

void Player::Collision(char axis, const std::string TileMap[], int H, int W) {
  for (int i = rect.top / Map::TileSize; i < (rect.top + rect.height) / Map::TileSize; i++)
    for (int j = rect.left / Map::TileSize; j < (rect.left + rect.width) / Map::TileSize; j++) {
      if (TileMap[i][j] == 'B') {
        if (axis == 'x') {  // Обработка столкновений по оси X
          if (dx > 0) {
            rect.left = static_cast<float>(j * Map::TileSize) - rect.width;
          }
          if (dx < 0) {
            rect.left = static_cast<float>(Map::TileSize * (j + 1));
          }
        } else if (axis == 'y') {  // Обработка столкновений по оси Y
          if (dy > 0) {
            rect.top = static_cast<float>(i * Map::TileSize) - rect.height;
            dy = 0;
            onGround = true;
          }
          if (dy < 0) {
            rect.top = static_cast<float>((i + 1) * Map::TileSize);
            dy = 0;
          }
        }
      } else if (TileMap[i][j] == 'E') { 
        win = true;  // Игрок коснулся "E"
      }
    }
}