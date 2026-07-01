cmake_minimum_required(VERSION 3.16)

project(YJDragGridConsumer LANGUAGES CXX)

find_package(YJDragGrid CONFIG REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(YJDragGridConsumer main.cpp)
target_link_libraries(YJDragGridConsumer PRIVATE YJDragGrid::YJDragGrid Qt${QT_VERSION_MAJOR}::Widgets)
