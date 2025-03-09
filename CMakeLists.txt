cmake_minimum_required(VERSION 3.5.0)
project(OtusBasicProject)

# Включаем Clang-Tidy
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy" -checks=*,-cppcoreguidelines-pro-bounds-pointer-arithmetic)
#set(CMAKE_CXX_CLANG_TIDY 
#    "clang-tidy" 
#    -checks=*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-llvmlibc-implementation-in-namespace,-llvmlibc-restrict-system-libc-headers,-llvmlibc-callee-namespace,-cppcoreguidelines-pro-bounds-array-to-pointer-decay,-hicpp-no-array-#decay
#)
# -llvmlibc-restrict-system-libc-headers разрешаем использование системного заголовочного файла <cmath>
#-checks=*,-llvmlibc-callee-namespace чтобы оператор operator[] был объявлен внутри пространства имён, заданного макросом LIBC_NAMESPACE
#-cppcoreguidelines-pro-bounds-array-to-pointer-decay  Отключает проверку на неявное преобразование массива в указатель из C++ Core Guidelines.
#-hicpp-no-array-decay Отключает аналогичную проверку.

# Включаем Clang-Tidy
set(CMAKE_CXX_CLANG_TIDY 
    "clang-tidy" 
    -checks=*,-cppcoreguidelines-pro-bounds-pointer-arithmetic
    # -llvmlibc-implementation-in-namespace,
    # -llvmlibc-restrict-system-libc-headers,
    # -llvmlibc-callee-namespace,
    # -cppcoreguidelines-pro-bounds-array-to-pointer-decay,
    # -hicpp-no-array-decay,
    # -fuchsia-default-arguments-calls,
    # -cppcoreguidelines-avoid-magic-numbers,
    # -readability-magic-numbers,
    # -altera-unroll-loops,
    # -bugprone-narrowing-conversions,
    # -cppcoreguidelines-narrowing-conversions,
    # -hicpp-braces-around-statements,
    # -readability-braces-around-statements,
    # -hicpp-uppercase-literal-suffix,
    # -readability-uppercase-literal-suffix,
    # -cppcoreguidelines-pro-type-member-init,
    # -hicpp-member-init,
    # -readability-function-cognitive-complexity
)


find_package(SFML REQUIRED graphics window system)


include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(OtusBasicProject ${SOURCES})

#target_include_directories(OtusBasicProject SYSTEM PRIVATE /usr/include/SFML/Graphics.hpp)

target_link_libraries(OtusBasicProject sfml-graphics sfml-window sfml-system)

set_target_properties(OtusBasicProject PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

# Копируем ресурсы (текстуры, шрифты) в папку сборки
file(COPY "resources/D_Boy.jpg" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "resources/Roboto.ttf" DESTINATION ${CMAKE_BINARY_DIR})


