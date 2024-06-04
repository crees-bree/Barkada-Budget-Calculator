# set cmake version
cmake_minimum_required(VERSION 3.0.0)

# set project name, version, and languages
project(Barkada-Budget-Calculator VERSION 1.0.0 LANGUAGES C CXX)

# locate ncurses package
# find_package(Curses REQUIRED)
# include_directories(${CURSES_INCLUDE_DIR})

# add -DNCURSES_STATIC as compile path (to compile ncurses on windows)
# SET(GCC_COVERAGE_COMPILE_FLAGS "-DNCURSES_STATIC")
# add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

# compile and link cpp files
add_executable(bbc 
               src/main.cpp
               lib/account.cpp 
               lib/date.cpp 
               lib/group_mode.cpp 
               lib/member.cpp 
               lib/person_mode.cpp 
               lib/profile.cpp
               lib/screen_util.cpp)

# link ncurses library
# target_link_libraries(bbc ${CURSES_LIBRARIES})
