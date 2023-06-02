#[=======================================================================[.rst:
FindQuEST
-------
 
Finds the QuEST library and creates a CMake target. Use QUEST_DIR and QUEST_LIB_DIR to specify the prefix path.

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``QUEST_FOUND``
True if libpetsc is found.
``QUEST_INCLUDE_DIRS``
Include directories needed to use PETSc.
``QUEST_LIBRARIES``
Libraries needed to link to PETSc.
``QUEST_LIBRARY_DIRS``
Location of libraries need to link to PETSc.

#]=======================================================================]

include(FindPackageHandleStandardArgs)

# QuEST is by default only built in place, and provides no install target, so no sense
# in trying pkgconfig

if (NOT DEFINED QUEST_DIR)
  set(QUEST_DIR $ENV{QUEST_DIR})
endif()
if (NOT DEFINED QUEST_LIB_DIR)
  set(QUEST_LIB_DIR $ENV{QUEST_LIB_DIR})
endif()

if ("${QUEST_DIR}" STREQUAL "")
  # We basically have no chance of finding it if this isn't set
  message(FATAL_ERROR "Please set the QUEST_DIR variable to the root QuEST directory.")
endif()

# search for header files
find_path(QUEST_INCLUDE_DIRS
  NAMES QuEST.h
  PATHS
    ${QUEST_DIR}/QuEST/include
)

# search for library
find_path(QUEST_LIBRARY_DIRS
  NAMES libQuEST.so
  PATHS
    ${QUEST_LIB_DIR}
    ${QUEST_DIR}/build/QuEST
)

if (QUEST_LIBRARY_DIRS)
  set(QUEST_LIBRARIES "QuEST")
endif()

find_package_handle_standard_args(QuEST
  REQUIRED_VARS
    QUEST_INCLUDE_DIRS
    QUEST_LIBRARIES
    QUEST_LIBRARY_DIRS
  REASON_FAILURE_MESSAGE
    "Try setting QUEST_DIR and QUEST_LIB_DIR. Current values shown below.
      QUEST_DIR=${QUEST_DIR}
      QUEST_LIB_DIR=${QUEST_LIB_DIR}"
)

if (QUEST_FOUND AND NOT TARGET QuEST::quest)
  add_library(QuEST::QuEST INTERFACE IMPORTED)
  target_include_directories(QuEST::QuEST INTERFACE ${QUEST_INCLUDE_DIRS})
  TARGET_LINK_LIBRARIES(QuEST::QuEST INTERFACE ${QUEST_LIBRARIES})
  target_link_directories(QuEST::QuEST INTERFACE ${QUEST_LIBRARY_DIRS})
endif()
