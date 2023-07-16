cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(tgl_tl_parser C)

find_package(ZLIB REQUIRED)

add_executable(${PROJECT_NAME}
	src/tl-parser.c
	src/tlc.c)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/tl_parser)
target_link_libraries(${PROJECT_NAME} PUBLIC ZLIB::ZLIB)

