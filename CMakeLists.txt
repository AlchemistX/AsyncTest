CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(AsyncTest)
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_VERBOSE_MAKEFILE True)

# we use this to get code coverage
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

ADD_SUBDIRECTORY(src)

INCLUDE(cmake/googletest.cmake)
fetch_googletest(
  ${PROJECT_SOURCE_DIR}/cmake
  ${PROJECT_BINARY_DIR}/googletest
)

ENABLE_TESTING()
ADD_SUBDIRECTORY(test)
