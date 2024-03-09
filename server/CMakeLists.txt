cmake_minimum_required(VERSION 3.1.2)

set(CMAKE_CXX_STANDARD 11)

set(PROJECT_NAME server)
project(${PROJECT_NAME})

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
	if ( "x${CMAKE_CONFIGURATION_TYPES}" STREQUAL "xRelease")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /MD")
	set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
	else()
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
	endif()

	add_definitions("-DUNICODE" "-D_UNICODE")
else()
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCE
		Src/*.cpp)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCE})
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

target_include_directories(
	${PROJECT_NAME}
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../include/thirdparty/cereal/include
	${CMAKE_CURRENT_SOURCE_DIR}/../include/thirdparty/cpp-httplib
	${CMAKE_CURRENT_SOURCE_DIR}/../include
	${CMAKE_INCLUDE_CURRENT_DIR}
)

install( FILES ${CMAKE_CURRENT_SOURCE_DIR}/build/${PROJECT_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../install)