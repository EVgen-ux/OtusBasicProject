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

    Player(sf::Texture &image);
    void update(float time, float &offsetX, float &offsetY); 
    void Collision(char axis, const std::string TileMap[], int H, int W);

   };

#endif // PLAYER_H