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
        util/string_utility/str_to_lower.c util/string_utility/str_contains_str.c
        util/unit_type_conversions/str_to_unit_type.c
        )

add_executable(str_to_lower util/string_utility/str_to_lower.c  ../src/util/string_utility.c ../src/util/string_utility.h)
add_executable(str_contains_str util/string_utility/str_contains_str.c ../src/util/string_utility.c ../src/util/string_utility.h)

add_executable(str_to_unit_type
        util/unit_type_conversions/str_to_unit_type.c
        ../src/util/unit_type_conversion.c ../src/util/unit_type_conversion.h
        ../src/data_manager/data_manager.c ../src/data_manager/data_manager.h
        ../src/util/string_utility.c       ../src/util/string_utility.h)

add_test(Str_to_lower str_to_lower)
add_test(Str_contains_str str_contains_str)

add_test(Str_to_unit_type str_to_unit_type)



target_include_directories(str_to_unit_type PUBLIC parson)
target_link_directories(str_to_unit_type PRIVATE  parson)
target_link_libraries(str_to_unit_type parson)