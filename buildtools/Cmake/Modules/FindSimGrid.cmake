#IF YOU HAVE INSTALL SIMGRID IN A SPECIAL DIRECTORY
#YOU CAN SPECIFY SIMGRID_ROOT OR GRAS_ROOT

# TO CALL THIS FILE USE
	#set(CMAKE_MODULE_PATH 
	#${CMAKE_MODULE_PATH}
	#${CMAKE_HOME_DIRECTORY}/buildtools/Cmake/Modules
	#)

find_library(HAVE_SIMGRID_LIB
    NAME simgrid
    HINTS
    $ENV{LD_LIBRARY_PATH}
    $ENV{GRAS_ROOT}
	$ENV{SIMGRID_ROOT}
    PATH_SUFFIXES lib64 lib
    PATHS
    /opt
    /opt/local
    /opt/csw
    /sw
    /usr
)

find_path(HAVE_GRAS_H gras.h
    HINTS
    $ENV{GRAS_ROOT}
	$ENV{SIMGRID_ROOT}
    PATH_SUFFIXES include
    PATHS
    /opt
    /opt/local
    /opt/csw
    /sw
    /usr
)

find_program(HAVE_TESH
	NAMES tesh
	HINTS
	$ENV{GRAS_ROOT}
	$ENV{SIMGRID_ROOT}
	PATH_SUFFIXES bin
	PATHS
	/opt
	/opt/local
	/opt/csw
	/sw
	/usr
)

find_program(HAVE_GRAS_STUB
	NAMES gras_stub_generator
	HINTS
	$ENV{GRAS_ROOT}
	$ENV{SIMGRID_ROOT}
	PATH_SUFFIXES bin
	PATHS
	/opt
	/opt/local
	/opt/csw
	/sw
	/usr
)

message(STATUS "Looking for lib SimGrid")
if(HAVE_SIMGRID_LIB)
message(STATUS "Looking for lib SimGrid - found")
else(HAVE_SIMGRID_LIB)
message(STATUS "Looking for lib SimGrid - not found")
endif(HAVE_SIMGRID_LIB)

message(STATUS "Looking for gras.h")
if(HAVE_GRAS_H)
message(STATUS "Looking for gras.h - found")
else(HAVE_GRAS_H)
message(STATUS "Looking for gras.h - not found")
endif(HAVE_GRAS_H)

if(HAVE_TESH)
message(STATUS "Found Tesh: ${HAVE_TESH}")
endif(HAVE_TESH)

if(HAVE_GRAS_STUB)
message(STATUS "Found gras_stub_generator: ${HAVE_GRAS_STUB}")
endif(HAVE_GRAS_STUB)