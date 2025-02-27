#include "Player.h"
#include "Map.h" // Подключаем заголовочный файл Map.h
#include <cmath>

Player::Player(sf::Texture &image) {
    sprite.setTexture(image);
    sprite.setTextureRect(sf::IntRect(47, 90, 45, 60));
    rect = sf::FloatRect(100, 210 - 60, 45, 60); // Начальная позиция на земле
    dx = dy = 0;
    curFrame = 0;
    onGround = true; // Персонаж на земле в начале игры
    win = false;
}

void Player::update(float time, float &offsetX, float &offsetY) {
    if (win) return; // Если игра завершена, не обновлять состояние игрока

    rect.left += dx * time;
    Collision('x', Map::TileMap, Map::H, Map::W); // Используем статические члены Map

    if (!onGround) dy = dy + 0.002 * time;
    rect.top += dy * time;
    onGround = false;

    Collision('y', Map::TileMap, Map::H, Map::W); // Используем статические члены Map

    curFrame += 0.005 * time;
    if (curFrame > 3) curFrame -= 3;

    if (dx > 0) sprite.setTextureRect(sf::IntRect(47 * int(curFrame), 90, 45, 60));
    if (dx < 0) sprite.setTextureRect(sf::IntRect(47 * int(curFrame) + 47, 90, -45, 60));

    sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
    dx = 0;
}

void Player::Collision(char axis, const std::string TileMap[], int H, int W) {
    for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
        for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
            if (TileMap[i][j] == 'B') {
                if (axis == 'x') { // Обработка столкновений по оси X
                    if (dx > 0) rect.left = j * 32 - rect.width;
                    if (dx < 0) rect.left = j * 32 + 32;
                } else if (axis == 'y') { // Обработка столкновений по оси Y
                    if (dy > 0) {
                        rect.top = i * 32 - rect.height;
                        dy = 0;
                        onGround = true;
                    }
                    if (dy < 0) {
                        rect.top = (i + 1) * 32;
                        dy = 0;
                    }
                }
            } else if (TileMap[i][j] == 'E') {
                win = true; // Игрок коснулся "E"
            }
        }
}