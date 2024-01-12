# cmake file for duilib
#Author Qi Gao(monkgau@gmail.com)
#modify lei liu(471971925@qq.com 20240109)
#Created: 2012/09/16

#print dir
message("duilib ${CMAKE_CURRENT_SOURCE_DIR} " ${CMAKE_CURRENT_SOURCE_DIR})
message("duilib build type:" ${BUILD_TYPE})
file(GLOB Root_src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB Control_src ${CMAKE_CURRENT_SOURCE_DIR}/Control/*.cpp)
file(GLOB Core_src ${CMAKE_CURRENT_SOURCE_DIR}/Core/*.cpp)
file(GLOB Layout_src ${CMAKE_CURRENT_SOURCE_DIR}/Layout/*.cpp)
file(GLOB Utils_src ${CMAKE_CURRENT_SOURCE_DIR}/Utils/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Utils/*.c)

file(GLOB Root_headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB Control_headers ${CMAKE_CURRENT_SOURCE_DIR}/Control/*.h)
file(GLOB Core_headers ${CMAKE_CURRENT_SOURCE_DIR}/Core/*.h)
file(GLOB Layout_headers ${CMAKE_CURRENT_SOURCE_DIR}/Layout/*.h)
file(GLOB Utils_headers ${CMAKE_CURRENT_SOURCE_DIR}/Utils/*.h)

#source_group("header files" ${Root_headers} ${Control_headers} ${Core_headers} ${Layout_headers} ${Utils_headers}) 
#source_group("source files" ${Root_src} ${Control_src} ${Core_src} ${Layout_src} ${Utils_src})

#keep folder tree mode
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Root_src} ${Control_src} ${Core_src} ${Layout_src} ${Utils_src} ${Root_headers} ${Control_headers} ${Core_headers} ${Layout_headers} ${Utils_headers})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Control)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Layout)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Utils)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#message(STATUS "PROJECT_SOURCE_DIR:"${PROJECT_SOURCE_DIR})
#if use static duilib
if(UILIB_STATIC)
	add_library(duilib STATIC ${Control_src} ${Core_src} ${Layout_src} ${Utils_src} ${Root_src} ${Root_headers} ${Control_headers} ${Core_headers} ${Layout_headers} ${Utils_headers})
else()
	add_library(duilib SHARED ${Control_src} ${Core_src} ${Layout_src} ${Utils_src} ${Root_src} ${Root_headers} ${Control_headers} ${Core_headers} ${Layout_headers} ${Utils_headers})
endif()

add_definitions(-DUILIB_EXPORTS)
target_link_libraries(duilib comctl32)

set_target_properties(duilib PROPERTIES OUTPUT_NAME "duilib")

#copy res dir
add_custom_command(TARGET duilib PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${PROJECT_SOURCE_DIR}/bin/ ${PROJECT_BINARY_DIR}/bin/Debug/
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${PROJECT_SOURCE_DIR}/bin/ ${PROJECT_BINARY_DIR}/bin/Release/)

if (NOT UILIB_STATIC)
  #to avoid copy duilib.dll error
  add_custom_command(TARGET duilib PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/lib/Debug
  COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/lib/Release
  COMMAND ${CMAKE_COMMAND} -E touch ${PROJECT_BINARY_DIR}/lib/Debug/duilib.dll
  COMMAND ${CMAKE_COMMAND} -E touch ${PROJECT_BINARY_DIR}/lib/Release/duilib.dll)

  #copy duilib dll to bin dir
  add_custom_command(TARGET duilib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${PROJECT_BINARY_DIR}/lib/Debug/duilib.dll ${PROJECT_BINARY_DIR}/bin/Debug/duilib.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${PROJECT_BINARY_DIR}/lib/Release/duilib.dll ${PROJECT_BINARY_DIR}/bin/Release/duilib.dll)
endif()
  
