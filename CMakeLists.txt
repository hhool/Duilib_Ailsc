# CMake root file for duilib related apps
#Date 2012-09-16
#Author: Qi Gao(monkgau@gmail.com)
#modify lei liu(471971925@qq.com 20240109)
#  CMake files for duilib
#  file for each app is under the related sub-dir
#

cmake_minimum_required(VERSION 2.8)

project(dui)

message(STATUS," CMake project files for duilib")

# this line is for UNICODE release,which is required by DuiDesigner 
# option use UNICODE ,default is true
option(UNICODE "use unicode mode" ON)
option(UILIB_STATIC "use static duilib" OFF)
option(MT "user runtime mt mode" OFF)

if(UNICODE)
	add_definitions(-DUNICODE -D_UNICODE)
endif()

if(UILIB_STATIC)
	add_definitions(-DUILIB_STATIC)
endif()

if(MT)
  #set_property(TARGET duilib PROPERTY
  #MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

# add each CMake file
add_subdirectory(duilib)
add_subdirectory(TestApp1)
add_subdirectory(VirtualListDemo)
add_subdirectory(PopupUIDemo)
add_subdirectory(MenuDemo)
add_subdirectory(LayeredDemo)
#add_subdirectory(ScrCapture)
#add_subdirectory(FlashDemo)
add_subdirectory(360SafeDemo)
add_subdirectory(QQDemo)
