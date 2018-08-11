cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
project(isorias)

execute_process(
		COMMAND git submodule foreach git pull origin master
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

#execute_process(
#		COMMAND git submodule update --remote --init
#		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
#)

add_custom_target(fengin-core WORKING_DIRECTORY modules/fengin-core)
add_custom_target(fengin-base WORKING_DIRECTORY modules/fengin-base)

function(find_static_library LIB_NAME OUT)
	if (WIN32 OR MSVC)
		set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
	elseif (UNIX)
		set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
	endif()
	find_library(
			FOUND_${LIB_NAME}_STATIC
			${LIB_NAME}
	)
	if (FOUND_${LIB_NAME}_STATIC)
		get_filename_component(ABS_FILE ${FOUND_${LIB_NAME}_STATIC} ABSOLUTE)
	else()
		message(SEND_ERROR "Unable to find library ${LIB_NAME}")
	endif()
	set(${OUT} ${ABS_FILE} PARENT_SCOPE)
endfunction()

file(GLOB GameObjects include/GameObjects/UI/* include/GameObjects/Game/*)
file(GLOB JsonCPP include/json/*.cpp include/json/*.hpp include/json/json/*.h)
set(SOURCE_FILES
		src/main.cpp
		src/Systems/Splashscreen.cpp
		src/Systems/Splashscreen.hpp
		src/Systems/Game.cpp
		src/Systems/Game.hpp
		${GameObjects}
		${JsonCPP}
		)

add_executable(isorias ${SOURCE_FILES})
include_directories(include modules modules/fengin-base/src libs/soil/src)
set_target_properties(isorias PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../)
find_library(SOIL SOIL HINTS ./libs/soil/lib)
if (UNIX)
	target_compile_options(isorias PUBLIC -W -Wall -Werror -Wextra -g3)
	find_library(FENGIN_CORE fengin-core HINTS ./modules/fengin-core/release)
	target_link_libraries(isorias dl ${FENGIN_CORE})
	target_link_libraries(isorias sfml-system sfml-window sfml-audio sfml-graphics)
endif (UNIX)
if (WIN32)
	find_library(FENDER fender HINTS ./lib)
	find_library(SFMLSYSTEM sfml-system HINTS ./lib)
	find_library(SFMLWINDOW sfml-window HINTS ./lib)
	find_library(SFMLAUDIO sfml-audio HINTS ./lib)
	find_library(SFMLGRAPHICS sfml-graphics HINTS ./lib)
	target_link_libraries(isorias ${FENDER})
	message("Found ${FENDER}")
	target_link_libraries(isorias ${SFMLSYSTEM} ${SFMLAUDIO} ${SFMLGRAPHICS} ${SFMLWINDOW})
endif (WIN32)
target_link_libraries(isorias -lstdc++fs)
