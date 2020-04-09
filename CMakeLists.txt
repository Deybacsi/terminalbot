cmake_minimum_required(VERSION 3.5)

project(terminalbot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wsign-compare -pthread -pipe")

#include_directories(3rdparty 3rdparty/jute)

set(SOURCE_FILES *.cpp *.h )

add_executable(terminalbot main.cpp)
target_link_libraries(${PROJECT_NAME} jsoncpp curl)
target_include_directories(${PROJECT_NAME} PRIVATE 3rdparty/plog/include )

#set(SOURCES "3rdparty/jute/jute.cpp")

#file(GLOB SOURCES SOURCE_FILES "3rdparty/jute/jute.cpp")
#add_executable(jute "3rdparty/jute/jute.cpp")
#add_executable(main "3rdparty/jute/main.cpp")


#add_subdirectory(3rdparty/jsoncpp)
#set(OPENSSL_USE_STATIC_LIBS TRUE)
#find_package(OpenSSL REQUIRED)


#target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto)
#target_link_libraries(${PROJECT_NAME} OpenSSL::SSL)
#target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})

#target_precompile_headers(${PROJECT_NAME} PUBLIC <iostream> config.h  3rdparty/cpp-httplib/httplib.h 3rdparty/json/single_include/nlohmann/json.hpp)
#target_precompile_headers(${PROJECT_NAME} PRIVATE "3rdparty/json/single_include/nlohmann/json.hpp" "3rdparty/cpp-httplib/httplib.h")
#target_precompile_headers(${PROJECT_NAME} PRIVATE "3rdparty/json/single_include/nlohmann/json.hpp" )

