# CMakeList.txt: проект CMake для Deque; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("Deque" LANGUAGES CXX)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Deque "src/main.cpp"  "src/Deque/deque.hpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
