cmake_minimum_required(VERSION 3.5)

if(POLICY CMP0025)
    cmake_policy(SET CMP0025 NEW)
endif()

project(socserver CXX)

if(NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra ")
endif()

find_package(mongocxx REQUIRED)

add_executable(${PROJECT_NAME} main.cpp  ${CMAKE_CURRENT_SOURCE_DIR}/server/SServer.cpp )

# Visual Studio pre 2017 requires boost polyfill.
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" AND CMAKE_CXX_STANDARD LESS 17)
  find_package(Boost 1.56.0 REQUIRED)
  if (CMAKE_VERSION VERSION_LESS 3.15.0)
    target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
  else()
    target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost)
  endif()
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIRECTORY}/server/  ${CMAKE_CURRENT_SOURCE_DIRECTORY}/db/  ${CMAKE_CURRENT_SOURCE_DIRECTORY}/model/)
target_link_libraries(${PROJECT_NAME} PRIVATE mongo::mongocxx_shared PRIVATE pthread)

add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
    
get_target_property(LIBMONGOCXX_DEFINITIONS mongo::mongocxx_shared INTERFACE_COMPILE_DEFINITIONS)
list(FIND LIBMONGOCXX_DEFINITIONS "BSONCXX_STATIC" LIST_IDX)
if (${LIST_IDX} GREATER -1)
    message(FATAL_ERROR "Expected BSONCXX_STATIC to not be defined")
endif()
list(FIND LIBMONGOCXX_DEFINITIONS "MONGOCXX_STATIC" LIST_IDX)
if (${LIST_IDX} GREATER -1)
    message(FATAL_ERROR "Expected MONGOCXX_STATIC to not be defined")
endif()
