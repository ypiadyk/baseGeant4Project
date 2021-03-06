project(baseGeant4Project)
cmake_minimum_required(VERSION 2.8)
MESSAGE( STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE Debug)
MESSAGE( STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

include(FindROOT.cmake)

MESSAGE( STATUS "ROOT_INCLUDE_DIR: ${ROOT_INCLUDE_DIR}")
MESSAGE( STATUS "ROOT_LIBRARY_DIR: ${ROOT_LIBRARY_DIR}")
MESSAGE( STATUS "ROOT_LIBRARIES: ${ROOT_LIBRARIES}")

INCLUDE_DIRECTORIES (${ROOT_INCLUDE_DIR})
LINK_DIRECTORIES(${ROOT_LIBRARY_DIR})

aux_source_directory(. SRC_LIST)
file(GLOB cc_sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB hh_headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB mac_files ${PROJECT_SOURCE_DIR}/*.mac)

find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include
                    ${Geant4_INCLUDE_DIR})

MESSAGE(STATUS "CMAKE_INCLUDE_PATH: " ${CMAKE_INCLUDE_PATH} )
message(STATUS "SRC_LIST: " ${SRC_LIST})
message(STATUS "hh_headers: " ${hh_headers})
message(STATUS "cc_sources: " ${cc_sources})

add_executable(${PROJECT_NAME} ${SRC_LIST} ${cc_sources} ${hh_headers} ${mac_files})
target_link_libraries(${PROJECT_NAME} ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

