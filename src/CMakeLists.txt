CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

include_directories(
  ${kazmath_SOURCE_DIR}/src
  ${glhck_SOURCE_DIR}/include
  ${Angelscript_SOURCE_DIR}/../../include
  ${Angelscript_SOURCE_DIR}/../../../add_on
  ../include
)

file(GLOB SOURCES *.cpp)
add_definitions(-DGLHCK_KAZMATH_FLOAT -DUSE_SINGLE_PRECISION)
add_library(anglhck ${SOURCES} ${AS_ADDONS}/scriptarray/scriptarray.cpp)

target_link_libraries(anglhck glhck Angelscript)

