set(PUCUTILS_PROD_LIB_OUTPUT_DIR "${SUBPROJECT_PROD_OUTPUT_DIR}/lib/pu")
set(PUCUTILS_PROD_INCLUDE_OUTPUT_DIR "${SUBPROJECT_PROD_OUTPUT_DIR}/include")

getSourceDir(PUCUTILS_SOURCE_DIR pucutils "${SOURCE_DIR}")

getSources(SOURCES pucutils "${SOURCE_DIR}")
getPrivateHeaders(PRIVATE_HEADERS pucutils "${SOURCE_DIR}")
getPublicHeaders(PUBLIC_HEADERS pucutils "${SOURCE_DIR}")
getFiles(TEST_FILES pucutils "${TEST_SOURCE_DIR}")

# TARGETS
add_library(pucutils SHARED)
add_dependencies(pucutils pucutilsHeaders)
target_sources(pucutils
	PRIVATE "${SOURCES}" "${PRIVATE_HEADERS}"
	PUBLIC "${PUBLIC_HEADERS}"
)
set_target_properties(pucutils PROPERTIES
	COMPILE_FLAGS "-D PUCUTILS_COMPILATION"
	LIBRARY_OUTPUT_DIRECTORY "${PUCUTILS_PROD_LIB_OUTPUT_DIR}"
)

list(TRANSFORM PUBLIC_HEADERS
	REPLACE "${SUBPROJECT_SOURCE_DIR}" "${PUCUTILS_PROD_INCLUDE_OUTPUT_DIR}"
	OUTPUT_VARIABLE OUTPUT_HEADERS
)
add_custom_target(pucutilsHeaders
	DEPENDS "${PUCUTILS_PROD_INCLUDE_OUTPUT_DIR}"
	COMMAND bash "${CMAKE_SOURCE_DIR}/bin/copyHeaders.sh"
		"${SUBPROJECT_SOURCE_DIR}" "${PUCUTILS_PROD_INCLUDE_OUTPUT_DIR}"
	SOURCES "${PUBLIC_HEADERS}"
	BYPRODUCTS "${OUTPUT_HEADERS}"
)
add_custom_command(
	COMMAND mkdir -p "${PUCUTILS_PROD_INCLUDE_OUTPUT_DIR}"
	OUTPUT "${PUCUTILS_PROD_INCLUDE_OUTPUT_DIR}"
	VERBATIM
)

add_executable(pucutilsTest)
add_dependencies(pucutilsTest puctest pucutils)
target_sources(pucutilsTest
	PRIVATE "${TEST_FILES}"
)
target_link_libraries(pucutilsTest
	PRIVATE puctest pucutils
)
target_include_directories(pucutilsTest
	PRIVATE "${SUBPROJECT_SOURCE_DIR}/"
)
set_target_properties(pucutilsTest PROPERTIES
	COMPILE_FLAGS "-D PUCUTILS_COMPILATION"
	RUNTIME_OUTPUT_DIRECTORY "${SUBPROJECT_TEST_OUTPUT_DIR}"
)