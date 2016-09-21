set(MY_PROJ_NAME dsn.tools.log.monitor.master)

# Source files under CURRENT project directory will be automatically included.
# You can manually set MY_PROJ_SRC to include source files under other directories.
set(MY_PROJ_SRC "")

# Search mode for source files under CURRENT project directory?
# "GLOB_RECURSE" for recursive search
# "GLOB" for non-recursive search
set(MY_SRC_SEARCH_MODE "GLOB")

set(MY_PROJ_INC_PATH "")

set(MY_PROJ_LIBS dsn.tools.log.monitor.common)

set(MY_BOOST_PACKAGES "")

set(MY_PROJ_LIB_PATH "")

# Extra files that will be installed
set(MY_BINPLACES "")

dsn_add_shared_library()

# file(COPY test/ DESTINATION "${CMAKE_BINARY_DIR}/test/${MY_PROJ_NAME}")

