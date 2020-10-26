cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

set(SHORT_NAME Ping_Test)
project(${SHORT_NAME})
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "Secret Project")
set(VITA_TITLEID  "VSDK00021")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
  src
)

file( GLOB SRCS src/*.c)

add_executable(${SHORT_NAME}
	${SRCS}
)

target_link_libraries(${SHORT_NAME}
  SDL2
  SDL2_ttf
  SDL2_image
  SDL2_mixer
  SDL2_net
  freetype
  png16
  z
  vita2d
  SceDisplay_stub
  SceCtrl_stub
  SceNet_stub
  SceSysmodule_stub
  SceAudio_stub
  SceSysmodule_stub
  SceGxm_stub
  SceCommonDialog_stub
  SceTouch_stub
  SceHid_stub
  m
)

file( GLOB_RECURSE ASSETS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} data/*)

set(VPKFILES "")

FOREACH(ITEM ${ASSETS})
  list(APPEND VPKFILES "FILE")
  list(APPEND VPKFILES ${ITEM})
  list(APPEND VPKFILES ${ITEM})
ENDFOREACH()

vita_create_self(${SHORT_NAME}.self ${SHORT_NAME})
vita_create_vpk(${SHORT_NAME}.vpk ${VITA_TITLEID} ${SHORT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
  ${VPKFILES}
)
