set(TARGET_NAME AXIS_TEST)

cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${TARGET_NAME})

set(Qt6_DIR "/Qt/6.9.3/msvc2022/lib/cmake/Qt6")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(spdlog REQUIRED)

qt_standard_project_setup()


set(QT_APP_HEADERS
        include/axis/app/local_logger.h
        include/axis/app/qt_loggerspace.h
        include/axis/app/qt_sink.h
)


set(QT_APP_SOURCES
        src/local_logger.cpp
        src/qt_loggerspace.cpp
        src/qt_sink.cpp
)

add_executable(${TARGET_NAME}
        qt_app.cpp
        src/local_logger.cpp
        src/qt_loggerspace.cpp
        src/qt_sink.cpp
)

target_include_directories(${TARGET_NAME} PRIVATE include)

target_link_libraries(${TARGET_NAME}
        Qt6::Core
        Qt6::Widgets
        spdlog::spdlog
)


