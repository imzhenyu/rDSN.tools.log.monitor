if (DEFINED DSN_CMAKE_INCLUDED)
else()
    project(dsn.tools.log.monitor C CXX)
    set(DSN_ROOT "$ENV{DSN_ROOT}")
    if(NOT EXISTS "${DSN_ROOT}/")
        message(FATAL_ERROR "Please make sure that ${DSN_ROOT} exists.")
    endif()

    include("${DSN_ROOT}/bin/dsn.cmake")
endif()

add_subdirectory(src)
