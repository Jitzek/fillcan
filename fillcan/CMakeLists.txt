cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project(
  Fillcan
  VERSION 0.1
  DESCRIPTION ""
)

file(GLOB SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/**/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/**/**/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/**/**/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/lib/glm/glm/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/lib/glm/glm/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/*.hpp
)

## Make Library
add_library(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

##############
## 	VULKAN	##
##############
## Set preprocessor defines
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNOMINMAX -D_USE_MATH_DEFINES")

## Clang specific
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-switch-enum")
endif()

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

## Compiler specific
IF(MSVC)
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
ENDIF(MSVC)

IF(UNIX)
	link_libraries(${XCB_LIBRARIES} ${Vulkan_LIBRARY})
ENDIF()

find_package(Vulkan)
include_directories(${VULKAN_INCLUDE_DIR})

IF(NOT Vulkan_FOUND)
  IF(WIN32)
	  find_library(Vulkan_LIBRARY NAMES vulkan-1 vulkan PATHS ${CMAKE_CURRENT_SOURCE_DIR}/lib/vulkan)
	  IF (Vulkan_LIBRARY)
		  set(Vulkan_FOUND ON)
		  message(STATUS "Using bundled Vulkan library version")
	  ENDIF()
  ENDIF()
  IF (UNIX)
		find_library(Vulkan_LIBRARY NAMES vulkan HINTS "$ENV{VULKAN_SDK}/lib" "${CMAKE_CURRENT_SOURCE_DIR}/lib/vulkan" REQUIRED)
		IF (Vulkan_LIBRARY)
			set(Vulkan_FOUND ON)
			message(STATUS "Using bundled Vulkan library version")
		ENDIF()
	ENDIF()
ENDIF()

IF (NOT Vulkan_FOUND)
	message(FATAL_ERROR "Could not find Vulkan library!")
ELSE()
	message(STATUS ${Vulkan_LIBRARY})
ENDIF()

IF (NOT Vulkan_FOUND)
	message(FATAL_ERROR "Could not find Vulkan library!")
ELSE()
  message(STATUS "Vulkan Found: ${Vulkan_LIBRARY})")
ENDIF()

link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARY})
######################
##	ENDOF VULKAN	##
######################

##############
## 	GLFW	##
##############
set(GLFW_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

include_directories(${GLFW_DIR})

add_subdirectory(${GLFW_DIR})
target_link_libraries(${PROJECT_NAME} glfw)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_DIR}/include)
target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)
##################
##	ENDOF GLFW	##
##################

##############
## 	GLM		##
##############
set(GLM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/glm")
include_directories(${GLM_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_DIR})
##################
##	ENDOF GLM	##
##################

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)