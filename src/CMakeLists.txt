cmake_minimum_required(VERSION 3.0.0)
project(Automatic-bargain-hunting-main VERSION 0.1.0)

set(SOURCES
        data_manager/data_loader.c  data_manager/data_loader.h
        data_manager/data_manager.c data_manager/data_manager.h
        data_manager/sort_stores.c  data_manager/sort_stores.h
        io/user_io.c                io/user_io.h
        search/search.c             search/search.h
        util/node_handler.c         util/node_handler.h
        util/string_utility.c       util/string_utility.h
        util/unit_type_conversion.c util/unit_type_conversion.h
        util/user_io_utility.c)

add_executable(${PROJECT_NAME} main.c ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC parson)
target_link_directories(${PROJECT_NAME} PRIVATE  parson)
target_link_libraries(${PROJECT_NAME} parson)

