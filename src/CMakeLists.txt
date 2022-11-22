cmake_minimum_required(VERSION 3.0.0)
project(Automatic-bargain-hunting-main VERSION 0.1.0)

add_executable(${PROJECT_NAME} main.c ../data_manager/data_manager.h ../data_manager/data_manager.c)
target_link_libraries(${PROJECT_NAME} parson)