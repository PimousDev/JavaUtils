cmake_minimum_required(VERSION 3.31.6)

project(ProjectUtils
	LANGUAGES C
)

set(SOURCE_DIR src)
set(TEST_SOURCE_DIR test)
set(OUTPUT_DIR out)
set(TEMPORARY_DIR tmp)

file(GLOB SUBPROJECTS_SOURCE_DIRS
	RELATIVE "${CMAKE_SOURCE_DIR}"
	"*/${SOURCE_DIR}"
)
list(TRANSFORM SUBPROJECTS_SOURCE_DIRS
	REPLACE "^([^/]+)/${SOURCE_DIR}$" "\\1"
	OUTPUT_VARIABLE SUBPROJECTS
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")

# GETTERS
function(getSourceDir variable subproject type)
	block(SCOPE_FOR VARIABLES)
		set(${variable} ${CMAKE_SOURCE_DIR}/${subproject}/${type})
		return(PROPAGATE ${variable})
	endblock()
endfunction()
function(getOutputDir variable subproject type)
	block(SCOPE_FOR VARIABLES)
		set(${variable} ${CMAKE_SOURCE_DIR}/out/${subproject}/${type})
		return(PROPAGATE ${variable})
	endblock()
endfunction()

function(getFiles variable subproject directory)
	file(GLOB_RECURSE FILES
		CONFIGURE_DEPENDS
		"${CMAKE_SOURCE_DIR}/${subproject}/${directory}/*.c"
		"${CMAKE_SOURCE_DIR}/${subproject}/${directory}/*.h"
	)

	block(SCOPE_FOR VARIABLES)
		set(${variable} ${FILES})
		return(PROPAGATE ${variable})
	endblock()
endfunction()
function(getSources variable subproject directory)
	block(SCOPE_FOR VARIABLES)
		getFiles(${variable} ${subproject} ${directory})
		list(FILTER ${variable} INCLUDE REGEX "^.+\.c$")
		return(PROPAGATE ${variable})
	endblock()
endfunction()
function(getHeaders variable subproject directory)
	block(SCOPE_FOR VARIABLES)
		getFiles(${variable} ${subproject} ${directory})
		list(FILTER ${variable} INCLUDE REGEX "^.+\.h$")
		return(PROPAGATE ${variable})
	endblock()
endfunction()
function(getPrivateHeaders variable subproject directory)
	block(SCOPE_FOR VARIABLES)
		getHeaders(${variable} ${subproject} ${directory})
		list(FILTER PRIVATE_HEADERS INCLUDE REGEX ".+\.inc\.h$")
		return(PROPAGATE ${variable})
	endblock()
endfunction()
function(getPublicHeaders variable subproject directory)
	block(SCOPE_FOR VARIABLES)
		getHeaders(${variable} ${subproject} ${directory})
		list(FILTER PRIVATE_HEADERS EXCLUDE REGEX ".+\.inc\.h$")
		return(PROPAGATE ${variable})
	endblock()
endfunction()

# SUBPROJECTS
foreach(SUBPROJECT ${SUBPROJECTS})
	message(STATUS "LOADING ${SUBPROJECT} SUBPROJECT...")

	getSourceDir(SUBPROJECT_SOURCE_DIR ${SUBPROJECT} ${SOURCE_DIR})

	getOutputDir(SUBPROJECT_DEV_OUTPUT_DIR ${SUBPROJECT} "dev")
	getOutputDir(SUBPROJECT_PROD_OUTPUT_DIR ${SUBPROJECT} "prod")
	getOutputDir(SUBPROJECT_TEST_OUTPUT_DIR ${SUBPROJECT} "test")

	add_subdirectory(${SUBPROJECT})
endforeach()