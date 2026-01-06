set(PUCUTILS_PROD_BIN_OUTPUT_DIR "${SUBPROJECT_PROD_OUTPUT_DIR}/bin")

getSources(SOURCES pu ${SOURCE_DIR})
list(FILTER SOURCES EXCLUDE REGEX ".+/pu.c$")
getPrivateHeaders(PRIVATE_HEADERS pucutils "${SOURCE_DIR}")
getPublicHeaders(PUBLIC_HEADERS pucutils "${SOURCE_DIR}")

# TARGETS
#add_executable(pu)
#add_dependencies(pu libpu pucutils)
#target_sources(pu
#	PRIVATE "${SUBPROJECT_SOURCE_DIR}/pu.c"
#)
#target_link_libraries(pu
#	PUBLIC libpu
#)
#set_target_properties(pu PROPERTIES
#	RUNTIME_OUTPUT_DIRECTORY "${PUCUTILS_PROD_BIN_OUTPUT_DIR}"
#)
#
#add_library(libpu STATIC)
#add_dependencies(libpu pucutils)
#target_sources(libpu
#	PRIVATE "${SOURCES}" "${PRIVATE_HEADERS}"
#	PUBLIC "${PUBLIC_HEADERS}"
#)
#set_target_properties(libpu PROPERTIES
#	OUTPUT_NAME pu
#	COMPILE_FLAGS "-D PU_COMPILATION"
#	ARCHIVE_OUTPUT_DIRECTORY "${SUBPROJECT_DEV_OUTPUT_DIR}"
#)