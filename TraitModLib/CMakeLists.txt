#	MYSQL_CPPCONN_DIR must be set

cmake_minimum_required(VERSION 3.15)
project(TraitModLib)

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "Please switch to x64 build.")
    return()
endif()

#	===============================================
set(MYSQL_CPPCONN_DIR $ENV{MYSQL_CPPCONN_DIR} CACHE PATH 
	"MySQL Connector/C++ 8.0 directory")
	
if(NOT MYSQL_CPPCONN_DIR)
	message(FATAL_ERROR
		"MYSQL_CPPCONN_DIR is not set!")
endif()

if(NOT EXISTS "${MYSQL_CPPCONN_DIR}/include/mysqlx/xdevapi.h")
	message(FATAL_ERROR
		"MySQL Connector/C++ headers not found!")
endif()

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/lib")

set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)

function(custom_add_library_from_dir TARGET)
    file(GLOB TARGET_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
    add_library(${TARGET} STATIC ${TARGET_SRC})
endfunction()

custom_add_library_from_dir(TraitModLib)

target_include_directories(TraitModLib PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/include
)

target_include_directories(TraitModLib PUBLIC
	$ENV{MYSQL_CPPCONN_DIR}/include
)