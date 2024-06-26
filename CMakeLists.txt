#----------------------------------------------------
# setup the project
#----------------------------------------------------

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(pgsproject)

#----------------------------------------------------
# find packages
#----------------------------------------------------

find_package(Geant4 REQUIRED ui_all vis_all) 
find_package(ROOT COMPONENTS REQUIRED)

#----------------------------------------------------
# include directory for this project
#----------------------------------------------------

include(${Geant4_USE_FILE})
include(${ROOT_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------
# locate sources and headers for this project
#----------------------------------------------------

file(GLOB sources ${PROJECT_SOURCE_DIR}/sources/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/headers/*.hh)

#----------------------------------------------------
# add the executable
#----------------------------------------------------

add_executable (main main.cc ${sources} ${headers})
target_link_libraries(main ${Geant4_LIBRARIES})
target_link_libraries(main ${ROOT_LIBRARIES})

#----------------------------------------------------
# move files to build
#----------------------------------------------------

set(main_SCRIPTS 
    macros/vis.mac
    macros/run.mac
    generator.mac)

foreach(_script ${main_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()


#----------------------------------------------------
# install the executable to 'bin'
#----------------------------------------------------

add_custom_target(pgsproject DEPENDS main)

#----------------------------------------------------
# Install the executable to 'bin' directory 
# under CMAKE_INSTALL_PREFIX
#----------------------------------------------------

install(TARGETS main DESTINATION bin)
