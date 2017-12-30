cmake_minimum_required(VERSION 2.8)
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_DEBUG_POSTFIX "d")

if (NOT MSVC)
  if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if (GCC_VERSION VERSION_LESS 4.7)
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else ()
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif ()
  else ()
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  endif ()
endif ()

find_package(OpenCV REQUIRED)
find_package(PCL 1.8 REQUIRED)

add_definitions(${PCL_DEFINITIONS})

find_path(PUPILTRACKER_INCLUDE_DIRS 
  NAMES pupiltracker/PupilTracker.h)

include_directories(
  include
  ${OpenCV_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${PUPILTRACKER_INCLUDE_DIRS}
  )

file(GLOB_RECURSE HEADERS *.h *.hpp) 
source_group("Include" FILES ${HEADERS})

set(source
  src/object.cpp
  src/pupil_tracker.cpp
  src/camera.cpp
  src/serial.cpp
  src/track_object.cpp
  src/object_manager.cpp
  src/eyetracker.cpp
  src/main.cpp
  src/viewer.cpp
  src/visualable.cpp
  src/surface.cpp
  )

find_library(PUPILTRACKER_LIBRARY
  NAMES "pupiltracker.lib"
  NO_DEFAULT_PATH)

find_library(PUPILTRACKER_LIBRARY_DEBUG
  NAMES "pupiltrackerd.lib"
  NO_DEFAULT_PATH)



add_executable(demo ${source} ${HEADERS})

IF (WIN32)
  target_link_libraries(demo debug ${PUPILTRACKER_LIBRARY_DEBUG})
  target_link_libraries(demo optimized PUPILTRACKER_LIBRARY)
  target_link_libraries(demo ${OpenCV_LIBS})
  target_link_libraries(demo ${PCL_LIBRARIES})
ELSEIF (UNIX)
  target_link_libraries(demo debug ${PUPILTRACKER_LIBRARY_DEBUG})
  target_link_libraries(demo optimized ${PUPILTRACKER_LIBRARY})
  target_link_libraries(demo ${OpenCV_LIBS} pthread)
  target_link_libraries(demo ${PCL_LIBRARIES})
ENDIF ()
