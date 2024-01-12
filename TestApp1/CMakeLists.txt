# cmake file for peoject
#Author lei liu(471971925@qq.com 20240109)
#Created: 2024/01/09

set(TARGET_NAME "TestApp1")

#print dir
message("${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR} " ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB Root_src ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB Root_headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

#keep folder tree mode
#source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${Root_src} ${Root_headers})
source_group("header files" ${Root_headers}) 
source_group("source files" ${Root_src})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#set exe dir
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(${TARGET_NAME} ${Root_src} ${Root_headers})

#set app is win32 windows app
set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
target_link_libraries(${TARGET_NAME} duilib)


