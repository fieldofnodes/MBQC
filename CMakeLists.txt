#######################################################################################
#######################################################################################
# Title   : CMakeLists.txt
# Author  : Jonathan Miller
# Date    : 31-May-2023 (20230531)
# Aim     : Project bulding an mbqc simulator
#         : Cmake file here calss Boost and QuEST
#         : Version 01
#         : 
#         :
#######################################################################################
#######################################################################################



# Stipulate minimum cmake version
cmake_minimum_required(VERSION 3.12)

# Set project name
project(MBQC VERSION 0.1)
# Starting message to show in cmake ..
message(STATUS "Running MBQC")
# Convey message in cmake
message(STATUS "Project version: ${PROJECT_VERSION}")
message(STATUS "To do:")
message(STATUS "")
message(STATUS "1. Finish writing code for graphFlowDefinition")
message(STATUS "2. Test graphFlowDefinition as written")
message(STATUS "")


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

#######################################################################################
#######################################################################################
# Set variables to files or paths needed for project compilation
# Set c++ version and add any warnings or flags.
# First set and find prackages from outside project root folder
#######################################################################################
#######################################################################################

# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)

# Suppresse deprecated declarations
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

# Set home root $HOME in linux (style of directory: /home/username/)
set(HOME_DIR $ENV{HOME})

# Set projects home folder
set(PROJECTS_DIR ${HOME_DIR}/Projects)

# Set the path to the QuEST library source directory
set(QUEST_DIR ${PROJECTS_DIR}/QuEST)


# Set the path to the QuEST library binary directory
set(QUEST_LIB_DIR ${QUEST_DIR}/build)




# Find Boost
find_package(Boost 1.81 REQUIRED)

if(Boost_FOUND)
    # Code to be executed if the Boost package is found
    message("Boost package found!")
    # Additional actions for when the package is found
else()
    # Code to be executed if the Boost package is not found
    message("Boost package not found!")
    # Additional actions for when the package is not found
endif()





# Find QuEST
find_package(QuEST REQUIRED)

#######################################################################################
#######################################################################################
# Set variables to files or paths needed for project compilation
# Set variable names to folders and files inside MBQC folder
#######################################################################################
#######################################################################################

# Set the source code directory variable
set(MBQC_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Set the figures directory variable
set(MBQC_FIGURE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/figs)

# Set the config code directory variable
set(MBQC_CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/config)

# Set the config code directory variable
set(MBQC_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Set generic helper functions folder
set(MBQC_HELPER_FUNC_DIR ${MBQC_SOURCE_DIR}/genericHelperFunctions)

# Set graph functions folder
set(MBQC_GRAPHS_DIR ${MBQC_SOURCE_DIR}/graphs)

# Set quantum graph functions folder
set(MBQC_QUANTUM_GRAPHS_DIR ${MBQC_SOURCE_DIR}/quantumGraphs)    

# Set test functions folder
set(MBQC_TEST_FUNCTIONS_DIR ${MBQC_SOURCE_DIR}/testFunctions)    
    
# Create variable to executables to run
set(MBQC_STARTER_FILE ${MBQC_SOURCE_DIR}/mbqcStarterFile.cpp)
set(TEST_NO_NOISE_SIMPLE_CIRCUITS_QUEST_FILE ${MBQC_TEST_DIR}/testNoNoiseSimpleCircuitsQuEST.cpp)
set(TEST_DAMPING_SIMPLE_CIRCUITS_QUEST_FILE ${MBQC_TEST_DIR}/testDampingSimpleCircuitsQuEST.cpp)

#######################################################################################
#######################################################################################
# Include directories for global use, 
# Initialise configuration file
# Add executable file and link libraries/directories
#######################################################################################
#######################################################################################

# Specify the include directories globally
include_directories(
    ${Boost_INCLUDE_DIRS}
    ${MBQC_SOURCE_DIR}
    ${MBQC_CONFIG_DIR}
    ${MBQC_FIGURE_DIR}
    ${MBQC_TEST_DIR}
    ${MBQC_HELPER_FUNC_DIR}
    ${MBQC_GRAPHS_DIR}
    ${MBQC_QUANTUM_GRAPHS_DIR}
    ${MBQC_TEST_FUNCTIONS_DIR})

# Configure the header file
configure_file(${MBQC_CONFIG_DIR}/config.h.in ${MBQC_CONFIG_DIR}/config.h)


if(TRUE)
    # Add your source files and executable targets here
    add_executable(mbqcStarterFile ${MBQC_STARTER_FILE})
    target_include_directories(mbqcStarterFile PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    target_link_libraries(mbqcStarterFile PRIVATE QuEST::QuEST ${Boost_LIBRARIES})
endif()

if(TRUE)
    # Set up testNoNoiseSimpleCircuitsQuEST
    add_executable(testNoNoiseSimpleCircuitsQuEST ${TEST_NO_NOISE_SIMPLE_CIRCUITS_QUEST_FILE})
    target_include_directories(testNoNoiseSimpleCircuitsQuEST PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    target_link_libraries(testNoNoiseSimpleCircuitsQuEST PRIVATE QuEST::QuEST  ${Boost_LIBRARIES})
endif()

if(TRUE)
    # Set up testNoNoiseSimpleCircuitsQuEST
    add_executable(testDampingSimpleCircuitsQuEST ${TEST_DAMPING_SIMPLE_CIRCUITS_QUEST_FILE})
    target_include_directories(testDampingSimpleCircuitsQuEST PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    target_link_libraries(testDampingSimpleCircuitsQuEST PRIVATE QuEST::QuEST  ${Boost_LIBRARIES})
endif()




