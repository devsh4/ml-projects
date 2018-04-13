# Generated 2018-04-12 18:43:06

cmake_minimum_required(VERSION 2.8.7)
set(TARGET TopMain)
project(${TARGET})

# require location of supporting RTS
if (NOT UMLRTS_ROOT)
  if (DEFINED ENV{UMLRTS_ROOT})
    set(UMLRTS_ROOT $ENV{UMLRTS_ROOT})
  else ()
    set(UMLRTS_ROOT /C:/Users/Dev/Downloads/Papyrus-RT/plugins/org.eclipse.papyrusrt.rts_1.0.0.201707181457/umlrts)
  endif ()
endif ()

# setup primary envars - provides tooling config
include(${UMLRTS_ROOT}/build/buildenv.cmake)

# model sources
set(SRCS TopMain.cc Tick.cc Dealer.cc Play.cc Player.cc Input.cc Top.cc TopControllers.cc )

# specify target
add_executable(${TARGET} ${SRCS})

# setup lib dependency support after defining TARGET
include(${UMLRTS_ROOT}/build/rtslib.cmake)

# compiler parameters
set_target_properties(${TARGET} PROPERTIES COMPILE_OPTIONS "${COPTS}")
set_target_properties(${TARGET} PROPERTIES COMPILE_DEFINITIONS "${CDEFS}")
include_directories(${INCS})

# linker parameters
set_target_properties(${TARGET} PROPERTIES CMAKE_EXE_LINKER_FLAGS "${LOPTS}")
target_link_libraries(${TARGET} ${LIBS})

