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
find_package(Boost REQUIRED)

include_directories(
  include
  ${OpenCV_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  )

set(source
  src/pupil_tracker.cpp
  src/object.cpp
  src/camera.cpp
  src/serial.cpp
  src/lightsensor_datacontroler.cpp
  src/lightsensor_dataprocessor.cpp
  src/track_object.cpp
  src/object_manager.cpp
  src/eyetracker.cpp
  src/main.cpp
  )

add_executable(demo ${source})

IF (WIN32)
  target_link_libraries(demo pupiltracker ${OpenCV_LIBS})
ELSEIF (UNIX)
  target_link_libraries(demo pupiltracker ${OpenCV_LIBS} pthread)
ENDIF ()
