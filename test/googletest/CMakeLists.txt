cmake_minimum_required(VERSION 3.14)

set(GTEST_OUT_DIR ${CMAKE_SOURCE_DIR}/../googletest/out)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
  SOURCE_DIR     ${GTEST_OUT_DIR}/src
  BINARY_DIR     ${GTEST_OUT_DIR}/bin
)

set(FETCHCONTENT_BASE_DIR ${GTEST_OUT_DIR})

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
endif ()

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})