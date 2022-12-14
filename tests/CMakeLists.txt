cmake_minimum_required(VERSION 3.0.0)
project(tests VERSION 0.1.0)

set(SOURCES
        ../src/data_manager/data_loader.c  ../src/data_manager/data_loader.h
        ../src/data_manager/data_manager.c ../src/data_manager/data_manager.h
        ../src/data_manager/rank_stores.c  ../src/data_manager/rank_stores.h
        ../src/data_manager/sort_stores.c  ../src/data_manager/sort_stores.h
        ../src/io/user_io.c                ../src/io/user_io.h
        ../src/search/search.c             ../src/search/search.h
        ../src/util/node_handler.c         ../src/util/node_handler.h
        ../src/util/string_utility.c       ../src/util/string_utility.h
        ../src/util/unit_type_conversion.c ../src/util/unit_type_conversion.h
        ../src/util/store_utility.c        ../src/util/store_utility.h
        ../src/util/user_io_utility.c      ../src/util/user_io_utility.h
        )


add_executable(user_io io/user_io.c ${SOURCES})
add_executable(data_manager data_manager/data_manager.c ${SOURCES})
add_executable(search search/search_store.c ${SOURCES})
add_executable(find_items search/find_items.c ${SOURCES})

target_include_directories(user_io PUBLIC parson)
target_link_directories(user_io PRIVATE  parson)
target_link_libraries(user_io parson)

target_include_directories(data_manager PUBLIC parson)
target_link_directories(data_manager PRIVATE  parson)
target_link_libraries(data_manager parson)

target_include_directories(search PUBLIC parson)
target_link_directories(search PRIVATE  parson)
target_link_libraries(search parson)

target_include_directories(find_items PUBLIC parson)
target_link_directories(find_items PRIVATE  parson)
target_link_libraries(find_items parson)

add_test(User_io user_io)
add_test(Data_manager data_manager)
add_test(Find_items find_items)
add_test(Search search)



