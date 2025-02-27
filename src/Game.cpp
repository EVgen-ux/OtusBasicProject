#include <iostream>
#include "Game.h"

Game::Game() : window(sf::VideoMode(600, 400), "Game!"), player(playerTexture) {
    if (!playerTexture.loadFromFile("D_Boy.jpg")) {
        std::cerr << "Ошибка загрузки текстуры персонажа!" << std::endl;
        exit(-1);
    }

    if (!font.loadFromFile("Roboto.ttf")) {
        std::cerr << "Ошибка загрузки шрифта!" << std::endl;
        exit(-1);
    }

    winText.setFont(font);
    winText.setString("You Win!");
    winText.setCharacterSize(50);
    winText.setFillColor(sf::Color::Red);
    winText.setStyle(sf::Text::Bold);
    winText.setPosition(200, 150);

    gameOver = false;
    offsetX = 0; // Инициализация offsetX
    offsetY = 0; // Инициализация offsetY
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        handleEvents();
        update(time);
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    if (!gameOver) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.dx = -0.2;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.dx = 0.2;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (player.onGround) {
                player.dy = -0.7;
                player.onGround = false;
            }
        }
    }
}

void Game::update(float time) {
    if (!gameOver) {
        player.update(time, offsetX, offsetY); // Передаем offsetX и offsetY

        // Рассчет смещения для скроллинга
        offsetX = player.rect.left + player.rect.width / 2 - 600 / 2;

        // Ограничение смещения, чтобы не выходить за границы карты
        if (offsetX < 0) offsetX = 0;
        if (offsetX > Map::W * 32 - 600) offsetX = Map::W * 32 - 600;

        if (player.win) {
            gameOver = true; // Остановка игры
        }
    }
}

void Game::render() {
    window.clear(sf::Color::White);

    Map::draw(window, offsetX, offsetY); // Передаем offsetX и offsetY
    window.draw(player.sprite);

    if (player.win) {
        window.draw(winText);
    }

    window.display();
}