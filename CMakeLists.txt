cmake_minimum_required(VERSION 3.5.0)


project(OtusBasicProject)

# Пытаемся найти предустановленный SFML
find_package(SFML REQUIRED graphics window system)

add_executable(OtusBasicProject main.cpp)

target_link_libraries(OtusBasicProject sfml-graphics sfml-window sfml-system)

set_target_properties(OtusBasicProject PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

# Копируем ресурсы (текстуры, шрифты) в папку сборки
file(COPY "D_Boy.jpg" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "Roboto.ttf" DESTINATION ${CMAKE_BINARY_DIR})