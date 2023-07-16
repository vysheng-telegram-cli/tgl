cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(tgl_crypto C)

find_package(OpenSSL REQUIRED COMPONENTS Crypto SSL)
find_package(ZLIB REQUIRED)

add_library(${PROJECT_NAME} STATIC
	src/aes_altern.c
	src/aes_openssl.c
	src/bn_altern.c
	src/bn_openssl.c
	src/err_altern.c
	src/err_openssl.c
	src/md5_altern.c
	src/md5_openssl.c
	src/rand_altern.c
	src/rand_openssl.c
	src/rsa_pem_altern.c
	src/rsa_pem_openssl.c
	src/sha_altern.c
	src/sha_openssl.c)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/crypto)
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(${PROJECT_NAME} PUBLIC OpenSSL::Crypto OpenSSL::SSL ZLIB::ZLIB)

