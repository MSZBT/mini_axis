set(Build_set 1)

set(TARGET_NAME AXIS_TEST)
if (${Build_set} EQUAL 1)
    cmake_minimum_required(VERSION 3.16)
    project(${TARGET_NAME})

    set(Qt6_DIR "D:/Programs_it/Qt/6.9.3/msvc2022/lib/cmake/Qt6")

    find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
    find_package(spdlog CONFIG REQUIRED)

    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    qt_standard_project_setup()

    add_executable(${TARGET_NAME} main.cpp)

    target_link_libraries(${TARGET_NAME}
            Qt6::Core
            Qt6::Widgets
            spdlog::spdlog
    )

elseif (${Build_set} EQUAL 2)
    cmake_minimum_required(VERSION 3.16)

    project(${TARGET_NAME})

    find_package(spdlog CONFIG REQUIRED)

    add_executable(${TARGET_NAME} Logger.cpp)

    target_link_libraries(${TARGET_NAME}
            spdlog::spdlog
    )
endif()