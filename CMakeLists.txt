cmake_minimum_required(VERSION 3.0)
project(hello)

###############################################################################
## file globbing ##############################################################
###############################################################################

# thise instructions search the directory tree when cmake is
# invoked and put all files that math the pattern in the variables 
# `sources` and `data`
file(GLOB sources src/*.cpp src/*.h)
file(GLOB_RECURSE assets)
# you can use set(sources src/main.cpp) etc if you don't want to
# use globbing to find files automatically

###############################################################################
## target definitions #########################################################
###############################################################################

# add the data to the target, so it becomes visible in some IDE
add_executable(hello ${sources} ${data})

# just for example add some compiler flags
target_compile_options(hello PUBLIC -std=c++1y -Wall)

# this lets me include files relative to the root src dir with a <> pair
target_include_directories(hello PUBLIC .) 

# this copies all resource files in the build directory
# we need this, because we want to work with paths relative to the executabl
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

###############################################################################
## dependencies ###############################################################
###############################################################################

link_directories(/usr/lib)

target_link_libraries(hello PUBLIC
  GL
  GLEW
  sfml-system
  sfml-window
  sfml-graphics
  )

###############################################################################
## packaging ##################################################################
###############################################################################

# all install commands get the same destination. this allows us to use paths
# relative to the executable.
install(TARGETS hello DESTINATION ./)
# this is basically a repeat of the file copy instruction that copies the
# resources in the build directory, but here we tell cmake that we want it
# in the package
install(DIRECTORY assets DESTINATION ./)

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
