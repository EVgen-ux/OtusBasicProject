# OtusBasicProject
## Тема: Разработка игры “Road to Freedom”

### Описание проекта
Игра представляет собой платформер, в котором игрок управляет персонажем, способным перемещаться по карте вперед, назад, прыгать и падать под действием силы тяжести. Цель игры — найти выход из заданного пространства, преодолевая препятствия.

---

## Установка и запуск на Linux

### Установка зависимостей

1. **Установка SFML**
Установите SFML с помощью пакетного менеджера вашего дистрибутива Linux.

Для дистрибутивов на основе **Debian/Ubuntu**:

```
sudo apt-get update
sudo apt-get install libsfml-dev
```
Для дистрибутивов на основе Fedora:

```
sudo dnf install SFML-devel
```
Для дистрибутивов на основе Arch Linux:
```
sudo pacman -S sfml
```

2. **Установка CMake**
Проект использует CMake для сборки, установите его:

```
sudo apt-get install cmake  # Для Debian/Ubuntu
sudo dnf install cmake      # Для Fedora
sudo pacman -S cmake        # Для Arch Linux
```

### Скачивание и сборка проекта
1. **Клонирование репозитория**
Склонируйте репозиторий с проектом на ваш компьютер:

```
git clone https://github.com/ваш-репозиторий/OtusBasicProject.git
cd OtusBasicProject
```
2. **Сборка проекта**
Dыполните следующие команды для сборки:
```
mkdir build
cd build
cmake ..
make
```
### Запуск программы

После успешной сборки проекта, запустите исполняемый файл:

```
./OtusBasicProject
```