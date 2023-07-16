cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(tgl C)

add_subdirectory(ThirdParty/crypto)
add_subdirectory(ThirdParty/tl-parser)

add_executable(${PROJECT_NAME}_generate
	src/generate.c
	src/tools.c)
target_include_directories(${PROJECT_NAME}_generate PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME}_generate PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/tgl)
target_include_directories(${PROJECT_NAME}_generate PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/crypto/include)
target_include_directories(${PROJECT_NAME}_generate PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/tl-parser/include)
target_link_libraries(${PROJECT_NAME}_generate ${PROJECT_NAME}_crypto)

list(APPEND GENERATE_COMMANDS
	skip-header
	fetch-header
	store-header
	autocomplete-header
	types-header
	fetch-ds-header
	free-ds-header
	store-ds-header
	print-ds-header
	skip
	fetch
	store
	autocomplete
	types
	fetch-ds
	free-ds
	store-ds
	print-ds)

list(APPEND GENERATE_OUTPUTS
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-skip.h
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-fetch.h
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-store.h
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-autocomplete.h
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-types.h
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-fetch-ds.h
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-free-ds.h
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-store-ds.h
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-print-ds.h
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-skip.c
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-fetch.c
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-store.c
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-autocomplete.c
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-types.c
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-fetch-ds.c
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-free-ds.c
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-store-ds.c
	${CMAKE_CURRENT_BINARY_DIR}/auto/auto-print-ds.c)

# TODO
set(TL_INPUTS
	${CMAKE_CURRENT_SOURCE_DIR}/tl/scheme.tl
	${CMAKE_CURRENT_SOURCE_DIR}/tl/encrypted_scheme.tl
	${CMAKE_CURRENT_SOURCE_DIR}/tl/binlog.tl
	${CMAKE_CURRENT_SOURCE_DIR}/tl/mtproto.tl
	${CMAKE_CURRENT_SOURCE_DIR}/tl/append.tl)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/auto/scheme.tl
	DEPENDS ${TL_INPUTS}
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/auto
	COMMAND ${CMAKE_COMMAND} -E cat ${TL_INPUTS} > ${CMAKE_CURRENT_BINARY_DIR}/auto/scheme.tl)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/auto/scheme2.tl
	DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/auto/scheme.tl
	COMMAND $<TARGET_FILE:tl-parser> -E ${CMAKE_CURRENT_BINARY_DIR}/auto/scheme.tl 2> ${CMAKE_CURRENT_BINARY_DIR}/auto/scheme2.tl)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/auto/constants.h
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/gen_constants_h.awk ${CMAKE_CURRENT_BINARY_DIR}/auto/scheme2.tl
	COMMAND awk -f ${CMAKE_CURRENT_SOURCE_DIR}/gen_constants_h.awk < ${CMAKE_CURRENT_BINARY_DIR}/auto/scheme2.tl > ${CMAKE_CURRENT_BINARY_DIR}/auto/constants.h)

add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/auto/scheme.tlo
	DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/auto/scheme.tl
	COMMAND $<TARGET_FILE:tl-parser> -e ${CMAKE_CURRENT_BINARY_DIR}/auto/scheme.tlo ${CMAKE_CURRENT_BINARY_DIR}/auto/scheme.tl)

foreach(GENERATE_COMMAND GENERATE_OUTPUT IN ZIP_LISTS GENERATE_COMMANDS GENERATE_OUTPUTS)
	add_custom_command(
		OUTPUT ${GENERATE_OUTPUT}
		DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/auto/scheme.tlo
		COMMAND $<TARGET_FILE:${PROJECT_NAME}_generate> -g ${GENERATE_COMMAND} ${CMAKE_CURRENT_BINARY_DIR}/auto/scheme.tlo > ${GENERATE_OUTPUT})
	set_source_files_properties(${GENERATE_OUTPUT} PROPERTIES GENERATED TRUE)
endforeach()

add_library(${PROJECT_NAME} STATIC
	src/mtproto-common.c
	src/mtproto-client.c
	src/mtproto-key.c
	src/queries.c
	src/structures.c
	src/binlog.c
	src/tgl.c
	src/tgl-net.c
	src/tgl-timers.c
	src/updates.c
	src/tg-mime-types.c
	src/mtproto-utils.c 
	src/tools.c
	${CMAKE_CURRENT_BINARY_DIR}/auto/constants.h
	${GENERATE_OUTPUTS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/tgl)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/tl-parser/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_crypto)

