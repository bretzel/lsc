
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
# Project name
project(Lsc VERSION 0.1.0 LANGUAGES CXX)
set(FrameWorkName "Lsc")

option(BUILD_REM "Enable building the Rem Utility library" ON)
option(BUILD_VAULT "Enable building the Vault/[SQLite,...] Database support  Library" ON)
option(BUILD_SCRIPTURE "Enable building the Scripture interpreter Library" ON)
option(BUILD_APPBOOK "Enable building the AppBook Library" ON)
option(BUILD_DIAGNOSTICS "Enable building the Diagnostics Library" OFF)

SET(LSC_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
SET(LSC_ROOT_PATH ${LSC_ROOT})

# testing noswap in nvim...
if(BUILD_REM)
    SET(REM_INCLUDE_DIR ${LSC_ROOT}/Rem/include)
    add_subdirectory(Rem)
endif()
# Crisse de bug?????! J'arrete JAMAIS DE DEVOIR CORRIGER LE CRISSE DE '}' C QUOI QUI INSERT CETTE CRISSE COCHONNERIE LÀ ?????? OSTIE!!!!!!!!!!!!!!!

if(BUILD_VAULT)
    SET(VAULT_INCLUDE_DIR ${LSC_ROOT}/Vault/include)
    add_subdirectory(Vault)
endif()

if(BUILD_SCRIPTURE)
    SET(SCRIPTURE_INCLUDE_DIR ${LSC_ROOT}/Scripture/include)
    add_subdirectory(Scripture)
endif()

if(BUILD_DIAGNOTICS)
    SET(DIAGNOSTICS_INCLUDE_DIR ${LSC_ROOT}/Diagnostics/include)
    add_subdirectory(Diagnostics)
endif()

if(BUILD_APPBOOK)
    SET(APPBOOK_INCLUDE_DIR ${LSC_ROOT}/AppBook/include)
    add_subdirectory(AppBook)
endif()


message ("Project SourceDir:" ${PROJECT_SOURCE_DIR})


IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
	EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
			${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
			)
ENDIF()


# uninstall target
if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
