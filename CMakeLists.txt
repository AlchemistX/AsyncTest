CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(AsyncTest)
SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_VERBOSE_MAKEFILE True)

OPTION(CodeCoverage "CodeCoverage" OFF)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# we use this to get code coverage
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  if (CMAKE_BUILD_TYPE MATCHES Debug)
    if (CodeCoverage MATCHES ON)
      INCLUDE(cmake/CodeCoverage.cmake)
      append_coverage_compiler_flags()
    endif()
  endif()
endif()

ADD_SUBDIRECTORY(src)

INCLUDE(cmake/googletest.cmake)
fetch_googletest(
  ${PROJECT_SOURCE_DIR}/cmake
  ${PROJECT_BINARY_DIR}/googletest
)

ENABLE_TESTING()
ADD_SUBDIRECTORY(test)
