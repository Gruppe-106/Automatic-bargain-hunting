cmake_minimum_required(VERSION 3.0.0)
project(Automatic-bargain-hunting VERSION 0.1.0)

include(CTest)
enable_testing()


add_subdirectory(examples)


# TODO: library inclutions

# add_subdirectory(libs)
# target_include_directories(${PROJECT_NAME} PUBLIC parson)
# target_link_directories(${PROJECT_NAME} PRIVATE  parson)
# target_link_libraries(${PROJECT_NAME} parson)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
