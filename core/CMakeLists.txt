##
 # @file CMakeLists.txt
 #
 # @brief CMake file for core directory / sub-directories
 #
 # @author Kishwar Kumar
 # Contact: kumar.kishwar@gmail.com
 # 
 # @date 13/03/2022
 #
 ##

 cmake_minimum_required(VERSION 3.16.0)

 file(GLOB_RECURSE SOURCE_C_FILES *.c)
 file(GLOB_RECURSE SOURCE_CPP_FILES *.cpp)

 set(INCLUDES "${CMAKE_SOURCE_DIR}/core"
              "${CMAKE_SOURCE_DIR}/core/hal/wifi"
              "${CMAKE_SOURCE_DIR}/inf")

 idf_component_register(SRCS ${SOURCE_C_FILES} ${SOURCE_CPP_FILES}
                        INCLUDE_DIRS ${INCLUDES}
                        PRIV_REQUIRES fatfs spiffs nvs_flash)