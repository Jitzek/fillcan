cmake_minimum_required(VERSION 3.8)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-pedantic-errors")
project(
  Fillcan-Application
  VERSION 0.1
  DESCRIPTION ""
)

## Set Debug and Release folders
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)

file(GLOB SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/apps/**/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/apps/**/*.hpp
)

set(SOURCE main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE} ${SOURCES})

## Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_EXTENSIONS OFF)

  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

##################
##  Platform    ##
##################
if (UNIX)
  message(STATUS "Detected Unix platform")
elseif(WIN32)
  message(STATUS "Detected Windows platform")
  if(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    ## If compiling with GCC/MinGW
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
  else()
    ## Probably compiling with VS build tools
    add_definitions( -DBOOST_ALL_NO_LIB )
    add_definitions( -DBOOST_ALL_DYN_LINK )
  endif()
endif()

if (MINGW)
  target_compile_options(${PROJECT_NAME} PRIVATE "-Wa,-mbig-obj")
endif()
######################
##  ENDOF Platform  ##
######################

set(Fillcan_DIRECTORY "${CMAKE_SOURCE_DIR}/fillcan")
target_include_directories(${PROJECT_NAME} PUBLIC ${Fillcan_DIRECTORY} ${PROJECT_BINARY_DIR})
# target_link_libraries (${PROJECT_NAME} ${Boost_LIBRARIES})

## Include Fillcan Library
add_subdirectory(${Fillcan_DIRECTORY})

## Link Fillcan Library to this project
target_link_libraries(${PROJECT_NAME} Fillcan)