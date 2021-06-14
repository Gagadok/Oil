cmake_minimum_required(VERSION 2.8.11)

project(Oil)

if($ENV{QT6_DIR})
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{QT6_DIR}/lib/cmake")
endif()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt6Widgets)
find_package(Qt6PrintSupport)

QT6_WRAP_UI(QT_UIS_HDRS
            mainwindow.ui)

# Tell CMake to create the helloworld executable
add_executable(Oil main.cpp
    mainwindow.cpp
    qcustomplot.cpp
    pythonfunctions.cpp
    ${QT_UIS_HDRS})

# Use the Widgets module from Qt 5.
target_link_libraries(Oil Qt6::Widgets Qt6::PrintSupport)
