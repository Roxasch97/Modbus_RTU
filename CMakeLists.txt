cmake_minimum_required(VERSION 3.14)

project(modbus_test CXX C)

add_subdirectory(test/googletest googletest)

set(INCLUDE_DIRS
	inc
)

set(TEST_INCLUDE_DIR
	test/modbus
)

set(SRCS
	src/ModbusRtu.c
	src/ModbusUtils.c
)

set(clang_dir
	src/ModbusRtu.c
	src/ModbusUtils.c
	inc/ModbusIO.h
	inc/ModbusRtu.h
	inc/ModbusTypes.h
	inc/ModbusUtils.h
	)

set(TEST_SRCS
	${TEST_INCLUDE_DIR}/modbus_requests_test.cpp
	${TEST_INCLUDE_DIR}/modbus_responses_test.cpp
	${TEST_INCLUDE_DIR}/ModbusIO_mock.cpp
)

add_custom_target(clang-format
	COMMAND clang-format -i -style=gnu ${clang_dir}
	COMMENT "Formatting code with Clang-Format"
	USES_TERMINAL
)

set(GLOBAL_DEFINES

)

add_executable(${CMAKE_PROJECT_NAME} ${SRCS} ${TEST_SRCS})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${INCLUDE_DIRS} ${TEST_INCLUDE_DIR})
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE ${GLOBAL_DEFINES})
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra)
target_link_libraries(${CMAKE_PROJECT_NAME} gtest_main gmock)

