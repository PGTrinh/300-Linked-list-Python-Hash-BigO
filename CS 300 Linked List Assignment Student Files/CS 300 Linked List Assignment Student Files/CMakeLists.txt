cmake_minimum_required(VERSION 3.0.0)
# Fix behavior of CMAKE_CXX_STANDARD when targeting macOS.
if (POLICY CMP0025)
cmake_policy(SET CMP0025 NEW)
endif ()
set (CMAKE_CXX_STANDARD 17)
project(bid VERSION 0.1.0)


include(CTest)
enable_testing()

add_library(csv-parser
  CSVparser.cpp
  CSVparser.hpp
)
set_property(TARGET csv-parser PROPERTY IMPORTED_LOCATION libcsv-parser.a)

add_executable(bid main.cpp)
link_directories(${CMAKE_SOURCE_DIR})
target_link_libraries(bid ${CMAKE_SOURCE_DIR}/libcsv-parser.a)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
