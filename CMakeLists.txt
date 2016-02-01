cmake_minimum_required(VERSION 3.0)
project(hello)


set(EXECUTABLE_NAME "hello")
###############################################################################
## file globbing ##############################################################
###############################################################################




if(CMAKE_GENERATOR MATCHES "Visual Studio 12 2013")
  set(CMAKE_CONFIGURATION_TYPES Debug Release)
  set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
    "Reset the configurations to what we need/support"
    FORCE
    )
  message(STATUS "Generating files with generator \"${CMAKE_GENERATOR}\"")
  message(STATUS "Please choose build configuration (\"Release\" or \"Debug\") in next step.")
ENDIF()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/Install" CACHE STRING "Cmake install path" FORCE)
endif()







# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

# Set version information in a config.h file
set(myproject_VERSION_MAJOR 1)
set(myproject_VERSION_MINOR 0)
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")


file(GLOB sources src/*.cpp src/*.h)

###############################################################################
## target definitions #########################################################
###############################################################################

# add the data to the target, so it becomes visible in some IDE
add_executable(${EXECUTABLE_NAME} ${sources})

# just for example add some compiler flags
target_compile_options(hello PUBLIC -std=c++1y -Wall)

# this lets me include files relative to the root src dir with a <> pair
target_include_directories(hello PUBLIC .) 

# this copies all resource files in the build directory
# we need this, because we want to work with paths relative to the executabl
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Install/bin")

###############################################################################
## dependencies ###############################################################
###############################################################################
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")

#find_package(OpenGL REQUIRED)
#find_package(EGL REQUIRED)
#find_package(FLAC)
#find_package(Freetype REQUIRED)
#find_package(GLES REQUIRED)
#find_package(SFML 2 REQUIRED system window graphics network audio)
#find_package(UDev)
#find_package(Vorbis)
#find_package(XCB)

find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()


# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
if (OPENGL_FOUND)
  target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
  # or: target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_gl_LIBRARY})
  target_link_libraries(${EXECUTABLE_NAME} m)  # if you use maths.h
endif()


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# now comse everything we need, to create a package
# there are a lot more variables you can set, and some
# you need to set for some package types, but we want to
# be minimal here
set(CPACK_PACKAGE_NAME "hello")
set(CPACK_PACKAGE_VERSION "1.0.0")

# we don't want to split our program up into several things
set(CPACK_MONOLITHIC_INSTALL 1)

# This must be last
include(CPack)
