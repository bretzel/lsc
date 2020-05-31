cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
# Project name

project(Rem VERSION 0.1.0 LANGUAGES CXX)


include(GNUInstallDirs)
#SET(REM_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include)
message("REM_INCLUDE_PATH:" ${REM_INCLUDE_DIR})
FILE(GLOB HDRS ${REM_INCLUDE_DIR}/*)
FILE(GLOB SRCS Src/*)
SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )




add_library(
        ${PROJECT_NAME}
        SHARED
        ${HDRS}
        ${SRCS}
		App/App.cpp App/App.h
)




target_compile_definitions(${PROJECT_NAME} PUBLIC "${PROJECT_NAME}_DEBUG=$<CONFIG:Debug>")
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

include(GenerateExportHeader)
#generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${${PROJECT_NAME}_export})

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
	EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
			${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
			)
ENDIF()

#if(PACKAGE_TESTS)
#    enable_testing()
#    include(googletest)
#    add_subdirectory(Tests)
#endif()

#set_target_properties(${PROJECT_NAME}
#        SOVERSION
#        )

target_include_directories(${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${REM_INCLUDE_DIR}>"
        $<INSTALL_INTERFACE:include/${FrameWorkName}/${PROJECT_NAME}>  # <prefix>/include/mylib
        )

target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS} sqlite3)


install(DIRECTORY
        include/${FrameWorkName}/${PROJECT_NAME}/
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${FrameWorkName}/${PROJECT_NAME}"
#        FILES_MATCHING PATTERN "*.h"
)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)


string(REPLACE "++" "" NS PROJECTNAME)

add_subdirectory(App)
