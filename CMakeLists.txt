cmake_minimum_required(VERSION 3.0.0)
project(Automatic-bargain-hunting VERSION 0.1.0)

include(CTest)
enable_testing()

# TODO: library inclutions
add_subdirectory(examples)
add_subdirectory(randomly_generated_testcases)
add_subdirectory(src)
add_subdirectory(libs/parson)
add_subdirectory(tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
