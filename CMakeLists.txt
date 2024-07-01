cmake_minimum_required(VERSION 3.16)

project(Calculator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
set(Qt6_DIR "C://Qt//6.8.0//msvc2022_64//lib//cmake//Qt6")
set(APP_ICON_RESOURCE_WINDOWS "res/app_icon.rc")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()
qt6_add_resources(QRCS res/resources.qrc)

set(Sources
    src/Main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
    ${QRCS}
)

if(WIN32)
    list(APPEND Sources ${APP_ICON_RESOURCE_WINDOWS})
endif()

qt_add_executable(Calculator ${Sources})

target_link_libraries(Calculator PRIVATE Qt6::Core Qt6::Widgets)
set_target_properties(Calculator PROPERTIES
    WIN32_EXECUTABLE ON
)
install(TARGETS Calculator)