cmake_minimum_required(VERSION 3.31)
project(BOSSlib 
    VERSION 0.1 LANGUAGES CXX
    )

set(CMAKE_CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

option(BUILD_TESTS "Build Simulation unit tests" ON)

# Skip the Catch2 tests, since nanoid already has them
# add_subdirectory(vendor/catch2)
add_subdirectory(vendor/nanoid_cpp)

file(GLOB_RECURSE BOSSLIB_SRC_FILES src/*.cpp)
file(GLOB_RECURSE BOSSLIB_INC_FILES inc/*.h)

add_library(bosslib ${BOSSLIB_SRC_FILES})
target_include_directories(bosslib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
  $<INSTALL_INTERFACE:inc>)

target_link_libraries(bosslib Threads::Threads nanoid)


#############################################
# Install
install(DIRECTORY inc/bosslib DESTINATION include)
install(TARGETS bosslib EXPORT bosslib-targets)
install(EXPORT bosslib-targets DESTINATION lib/cmake/bosslib)

# # Config files for find_package()
include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/bosslib-config.cmake"
  INSTALL_DESTINATION lib/cmake/bosslib)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/bosslib-version.cmake"
    VERSION "0.1"
    COMPATIBILITY AnyNewerVersion)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/bosslib-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/bosslib-version.cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindBOSSlib.cmake"
    DESTINATION lib/cmake/bosslib)
export(EXPORT bosslib-targets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/bosslib-targets.cmake")

#############################################
# Unit tests
if (BUILD_TESTS)
    enable_testing()
    add_executable(tests test/test.cpp)

    target_link_libraries(tests bosslib Catch2::Test)

    add_test(test_all tests)
    message(STATUS "Added tests to build")
endif()

