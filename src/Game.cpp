#include "Game.h"
#include <iostream>
#include <stdexcept>

Game::Game() : window(sf::VideoMode(600, 400), "Game!"), player(playerTexture) {
  if (!playerTexture.loadFromFile("D_Boy.jpg")) {
    throw std::runtime_error("Ошибка загрузки текстуры персонажа!");
  }

  if (!font.loadFromFile("Roboto.ttf")) {
    throw std::runtime_error("Ошибка загрузки шрифта!");
  }

  winText.setFont(font);
  winText.setString("You Win!");
  winText.setCharacterSize(50);
  winText.setFillColor(sf::Color::Green);
  winText.setStyle(sf::Text::Bold);
  winText.setPosition(200, 150);

  loseText.setFont(font); // Инициализация текста для проигрыша
  loseText.setString("You Lose!");
  loseText.setCharacterSize(50);
  loseText.setFillColor(sf::Color::Red);
  loseText.setStyle(sf::Text::Bold);
  loseText.setPosition(200, 150);

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
    offsetX = player.rect.left + player.rect.width / 2 - 600.f / 2;

    // Ограничение смещения, чтобы не выходить за границы карты
    if (offsetX < 0)
      offsetX = 0;
    if (offsetX > Map::W * 32 - 600)
      offsetX = Map::W * 32 - 600;

    if (player.win) {
      gameOver = true;            // Остановка игры
    } else if (player.gameOver) { // Проверка на проигрыш
      gameOver = true;
    }
  }
}

void Game::render() {
  window.clear(sf::Color::White);

  Map::draw(window, offsetX, offsetY); // Передаем offsetX и offsetY
  drawObject(window, player, offsetX, offsetY); // Используем шаблонную функцию

  if (player.win) {
    window.draw(winText);
  } else if (gameOver) {
    window.draw(loseText);
  }

  window.display();
}
