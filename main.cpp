#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

int ground = 210; // Уровень земли

float offsetX = 0, offsetY = 0;

const int H = 12;
const int W = 40;

String TileMap[H] = {
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

class PLAYER {
public:
    float dx, dy;
    FloatRect rect;
    bool onGround;
    Sprite sprite;
    float curFrame;
    bool win;

    PLAYER(Texture &image) {
        sprite.setTexture(image);
        sprite.setTextureRect(IntRect(47, 90, 45, 60));
        rect = FloatRect(100, ground - 60, 45, 60); // Начальная позиция на земле
        dx = dy = 0;
        curFrame = 0;
        onGround = true; // Персонаж на земле в начале игры
        win = false;
    }

    void update(float time) {
        if (win) return; // Если игра завершена, не обновлять состояние игрока

        rect.left += dx * time;

        Collision('x'); // Проверка столкновений по оси X

        if (!onGround) dy = dy + 0.0025 * time;

        rect.top += dy * time;

        onGround = false;

        Collision('y'); // Проверка столкновений по оси Y

        curFrame += 0.005 * time;
        if (curFrame > 3) curFrame -= 3;

        if (dx > 0) sprite.setTextureRect(IntRect(47 * int(curFrame), 90, 45, 60));
        if (dx < 0) sprite.setTextureRect(IntRect(47 * int(curFrame) + 47, 90, -45, 60));

        sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

        dx = 0;
    }

    void Collision(char axis) {
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
};

int main() {
    RenderWindow window(VideoMode(600, 400), "Test!");

    // Загрузка текстуры персонажа
    Texture PlayerTex;
    if (!PlayerTex.loadFromFile("D_Boy.jpg")) {
        std::cerr << "Ошибка загрузки текстуры персонажа!" << std::endl;
        return -1;
    }

    PLAYER P(PlayerTex);

    Clock clock;

    RectangleShape rectangle;
    rectangle.setSize(Vector2f(32, 32)); // Размер блока

    Font font;
    if (!font.loadFromFile("Roboto.ttf")) {
        std::cerr << "Ошибка загрузки шрифта!" << std::endl;
        return -1;
    }

    Text winText;
    winText.setFont(font);
    winText.setString("You Win!");
    winText.setCharacterSize(50);
    winText.setFillColor(Color::Red);
    winText.setStyle(Text::Bold);
    winText.setPosition(200, 150);

    bool gameOver = false; // Флаг завершения игры

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        if (!gameOver) {
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                P.dx = -0.1;
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                P.dx = 0.1;
            }

            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                if (P.onGround) {
                    P.dy = -0.7;
                    P.onGround = false;
                }
            }

            P.update(time);

            // Рассчет смещения для скроллинга
            offsetX = P.rect.left + P.rect.width / 2 - 600 / 2;

            // Ограничение смещения, чтобы не выходить за границы карты
            if (offsetX < 0) offsetX = 0;
            if (offsetX > W * 32 - 600) offsetX = W * 32 - 600;

            if (P.win) {
                gameOver = true; // Остановка игры
            }
        }

        window.clear(Color::White);

        // Отрисовка карты
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (TileMap[i][j] == 'B') rectangle.setFillColor(Color::Black);
                if (TileMap[i][j] == 'E') rectangle.setFillColor(Color::Green);
                if (TileMap[i][j] == ' ') continue;

                rectangle.setPosition(j * 32 - offsetX, i * 32 - offsetY);
                window.draw(rectangle);
            }
        }

        window.draw(P.sprite);

        if (P.win) {
            window.draw(winText);
        }

        window.display();
    }

    return 0;
}