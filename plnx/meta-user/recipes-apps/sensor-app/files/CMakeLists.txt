cmake_minimum_required(VERSION 3.12)

project(sensor-app)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Qml Quick)

add_executable(${PROJECT_NAME} main.cpp mydatamodel.cpp qml.qrc)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Qml Qt5::Quick)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
