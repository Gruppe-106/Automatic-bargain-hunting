cmake_minimum_required(VERSION 3.0.0)
project(Automatic-bargain-hunting-main VERSION 0.1.0)

set(SOURCES
        data_manager/data_manager.c
        data_manager/data_manager.h
        search/search.c search/search.h data_manager/sort_stores.c data_manager/sort_stores.h util/string_utility.c util/string_utility.h)

add_executable(${PROJECT_NAME} main.c ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC parson)
target_link_directories(${PROJECT_NAME} PRIVATE  parson)
target_link_libraries(${PROJECT_NAME} parson)