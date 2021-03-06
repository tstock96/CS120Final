cmake_minimum_required(VERSION 3.7)
project(graphics)

set(FREEGLUT_INCLUDE_DIRS "C:/Program\ Files/Common\ Files/freeglut/include")
set(FREEGLUT_LIBRARY_DIRS "C:/Program\ Files/Common\ Files/freeglut/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wno-deprecated")

find_package (OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR}  ${FREEGLUT_INCLUDE_DIRS})
link_directories(${FREEGLUT_LIBRARY_DIRS})

file(GLOB SOURCE_FILES
        *.cpp
        *.h
        )

add_executable(main.cpp ${SOURCE_FILES} fueltank.h fueltank.cpp graphics.h graphics.cpp shapes.h shapes.cpp)

target_link_libraries (main.cpp ${OPENGL_LIBRARIES} freeglut)