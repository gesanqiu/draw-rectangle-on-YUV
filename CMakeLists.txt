# created by Ricardo Lu 06-07-21

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)

PROJECT(osdyuv)

include_directories(
    ./inc
)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/lib)

add_library(${PROJECT_NAME}
    SHARED
    src/osdyuv.cpp
)

add_executable(${PROJECT_NAME}test
    # drawRectNV12.cpp
    src/test.cpp
)

target_link_libraries(${PROJECT_NAME}test
    ${PROJECT_NAME}
)

file(GLOB LIBRARY_INCLUDE_FILES ./inc/*.h)

install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION /opt/thundersoft/thirdparty/lib
)

install(
    FILES ${LIBRARY_INCLUDE_FILES}
    DESTINATION /opt/thundersoft/thirdparty/inc
)