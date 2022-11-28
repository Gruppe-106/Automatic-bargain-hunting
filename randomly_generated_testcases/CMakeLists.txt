cmake_minimum_required(VERSION 3.0.0)
project(test-1 VERSION 0.1.0)

set(SOURCES
        ../src/data_manager/data_manager.c ../src/data_manager/data_manager.h
        ../src/data_manager/rank_stores.c  ../src/data_manager/rank_stores.h
        ../src/data_manager/sort_stores.c  ../src/data_manager/sort_stores.h
        ../src/io/user_io.c                ../src/io/user_io.h
        ../src/search/search.c             ../src/search/search.h
        ../src/util/node_handler.c         ../src/util/node_handler.h
        ../src/util/string_utility.c       ../src/util/string_utility.h
        ../src/util/unit_type_conversion.c ../src/util/unit_type_conversion.h)

add_executable(${PROJECT_NAME} test1.c ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC parson)
target_link_directories(${PROJECT_NAME} PRIVATE  parson)
target_link_libraries(${PROJECT_NAME} parson)
