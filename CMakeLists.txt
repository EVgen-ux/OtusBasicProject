cmake_minimum_required(VERSION 3.5.0)
project(OtusBasicProject)


find_package(SFML REQUIRED graphics window system)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(OtusBasicProject ${SOURCES})

target_link_libraries(OtusBasicProject sfml-graphics sfml-window sfml-system)

set_target_properties(OtusBasicProject PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

# Копируем ресурсы (текстуры, шрифты) в папку сборки
file(COPY "resources/D_Boy.jpg" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "resources/Roboto.ttf" DESTINATION ${CMAKE_BINARY_DIR})