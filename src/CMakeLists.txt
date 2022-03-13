##
 # @file CMakeLists.txt
 #
 # @brief CMake file for main source directory
 #
 # @author Kishwar Kumar
 # Contact: kumar.kishwar@gmail.com
 # 
 # @date 13/02/2022
 #
 ##

 idf_component_register(SRCS "main.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES nvs_flash)
 