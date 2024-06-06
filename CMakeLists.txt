# set cmake version
cmake_minimum_required(VERSION 3.0.0)

# set project name, version, and languages
project(BBC VERSION 0.1.0 LANGUAGES C CXX)
set(VERSION_TYPE "alpha" CACHE STRING "version type" FORCE)

# locate ncurses package
# find_package(Curses REQUIRED)
# include_directories(${CURSES_INCLUDE_DIR})

# add -DNCURSES_STATIC as compile path (to compile ncurses on windows)
# SET(GCC_COVERAGE_COMPILE_FLAGS "-DNCURSES_STATIC")
# add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

add_executable(bbc 
               src/main.cpp
               assets/BBCIcon.rc
               )

add_subdirectory(ascii)
add_subdirectory(profile)
add_subdirectory(lib)

# link ncurses library
# target_link_libraries(bbc ${CURSES_LIBRARIES})

# link bbclib core library to bbc
target_include_directories(bbc PUBLIC "lib")
target_link_directories(bbc PUBLIC "lib")
target_link_libraries(bbc PUBLIC bbclib)

# configure version variables
configure_file(BBCConfig.h.in BBCConfig.h)

# include version headers
install(FILES "${PROJECT_BINARY_DIR}/BBCConfig.h" DESTINATION include)

include(InstallRequiredSystemLibraries)

# install executable to bin directory
install(TARGETS bbc DESTINATION bin)

set(CPACK_PACKAGE_EXECUTABLES "bbc" "Barkada Budget Calculator")
set(CPACK_CREATE_DESKTOP_LINKS "bbc")
set(CPACK_STRIP_FILES TRUE)

# windows installer config
set(CPACK_PACKAGE_NAME "Barkada Budget Calculator")
set(CPACK_PACKAGE_VENDOR "The BLM Group")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Barkada Budget Calculator is a money tracker suitable for personal and group use.")
set(CPACK_PACKAGE_VERSION_MAJOR "${BBC_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${BBC_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${BBC_VERSION_PATCH}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/crees-bree/Barkada-Budget-Calculator")
set (CPACK_NSIS_MODIFY_PATH "ON")


set(CPACK_NSIS_INSTALLED_ICON_NAME "${CMAKE_CURRENT_SOURCE_DIR}build/bbc.exe")

# Icons
set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/assets\\\\bbclogo.ico")
set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/assets\\\\SetupClassicIcon.ico")
set(CPACK_NSIS_MUI_UNIICON "${CMAKE_CURRENT_SOURCE_DIR}/assets\\\\SetupClassicIcon.ico")

include(CPack)

