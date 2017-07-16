cmake_minimum_required(VERSION 3.7)
project(QtQuickPlayground)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)
set(CMAKE_PREFIX_PATH $ENV{QT_CMAKE})

find_package(Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt5Core REQUIRED)
file(GLOB SOURCES "src/main/cpp/*.cpp" "src/main/cpp/*.h" "src/main/resources/*")

add_executable(${PROJECT_NAME} ${SOURCES} src/main/cpp/VideoListModel.cpp src/main/cpp/VideoListModel.h)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick)