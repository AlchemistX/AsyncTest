FIND_PACKAGE(PkgConfig REQUIRED)
PKG_SEARCH_MODULE(GLIB2 REQUIRED glib-2.0)

ADD_EXECUTABLE(EventQueueTest
  EventQueueTest.cpp
  Notification.cpp
  ${PROJECT_SOURCE_DIR}/src/Utility.cpp
  ${PROJECT_SOURCE_DIR}/src/EventQueue.cpp)

TARGET_LINK_LIBRARIES(EventQueueTest PUBLIC ${GLIB2_LIBRARIES} pthread gtest_main gmock_main)
TARGET_INCLUDE_DIRECTORIES(EventQueueTest PUBLIC ${GLIB2_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src)
TARGET_COMPILE_OPTIONS(EventQueueTest PUBLIC ${GLIB2_CFLAGS_OTHER})

ADD_TEST(
  NAME EventQueueTest
  COMMAND ${CMAKE_BINARY_DIR}/test/EventQueueTest
)

# we use this to get code coverage
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  if (CMAKE_BUILD_TYPE MATCHES Debug)
    if (CodeCoverage MATCHES ON)
      setup_target_for_coverage_lcov(
        NAME coverage
        EXECUTABLE ${CMAKE_BINARY_DIR}/test/EventQueueTest
        EXCLUDE "${CMAKE_BINARY_DIR}/googletest/*" "/usr/*")
    endif()
  endif()
endif()

