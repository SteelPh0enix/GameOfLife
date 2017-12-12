# Initial configuration
cmake_minimum_required(VERSION 3.0)

# SFML and TGUI include/library directories
set(SFML_INCLUDE_DIRECTORY "/usr/include" CACHE PATH "SFML include directory")
set(SFML_LIB_DIRECTORY "/usr/lib" CACHE PATH "SFML libraries directory")
set(TGUI_INCLUDE_DIRECTORY "/usr/include" CACHE PATH "TGUI include directory")
set(TGUI_LIB_DIRECTORY "/usr/lib" CACHE PATH "TGUI libraries directory")

# SFML libraries configuration
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(SFML_LIBS sfml-system-d sfml-window-d sfml-graphics-d)
  set(TGUI_LIBS tgui-d)
else()
  set(TGUI_LIBS tgui)
  if (WIN32)
    set(SFML_LIBS sfml-main sfml-system sfml-window sfml-graphics)
  else()
    set(SFML_LIBS sfml-system sfml-window sfml-graphics)
  endif()
endif()

# Project configuration
project(GameOfLife)
set(CMAKE_CXX_STANDARD 14)

# Find sources, add executable, link libraries
include_directories(${SFML_INCLUDE_DIRECTORY}
                    ${TGUI_INCLUDE_DIRECTORY}
                    ${PROJECT_SOURCE_DIR}
                    ${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES src/*.cpp)
link_directories(${SFML_LIB_DIRECTORY} ${TGUI_LIB_DIRECTORY})
if(WIN32 AND CMAKE_BUILD_TYPE MATCHES Release)
  add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
else()
  add_executable(${PROJECT_NAME} ${SOURCES})
endif()

target_link_libraries(${PROJECT_NAME} ${SFML_LIBS} ${TGUI_LIBS})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
