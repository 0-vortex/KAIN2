cmake_minimum_required (VERSION 3.0)

project (KAIN2_PSX${TARGET_ARCH})

#Additional library include directories
include_directories("c:/psyq/include")
link_directories("c:/psyq/lib")

#Recursively locate the source files for SPEC_PSX.
file(GLOB_RECURSE PSX_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.C  ${CMAKE_CURRENT_SOURCE_DIR}/*.H ${CMAKE_CURRENT_SOURCE_DIR}/*.CUR ${CMAKE_CURRENT_SOURCE_DIR}/*.RC)

#Group solution source files to correct folders.
source_group("PSX" FILES ${PSX_SRCS})
source_group("G2" FILES ${GLOBAL_G2_SRCS})
source_group("MONSTER" FILES ${GLOBAL_MONSTER_SRCS})
source_group("PLAN" FILES ${GLOBAL_PLAN_SRCS})
source_group("RAZIEL" FILES ${GLOBAL_RAZIEL_SRCS})

#Setup include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/PSX_G2)
include_directories(${GAME_CODE_DIR})
include_directories(${G2_CODE_DIR})
include_directories(${MONSTER_CODE_DIR})
include_directories(${PLAN_CODE_DIR})
include_directories(${RAZIEL_CODE_DIR})

add_executable(
${PROJECT_NAME}
${GLOBAL_GAME_SRCS}
${GLOBAL_G2_SRCS}
${GLOBAL_MONSTER_SRCS}
${GLOBAL_PLAN_SRCS}
${GLOBAL_RAZIEL_SRCS}
${PSX_SRCS}
)

#Link against required libraries
#target_link_libraries(
#${PROJECT_NAME}
#)

set_target_properties(
${PROJECT_NAME} PROPERTIES OUTPUT_NAME "KAIN2"
${PROJECT_NAME} PROPERTIES FOLDER "Build Targets/PlayStation"
)

#This will be a console application, alter linker subsystem accordingly or main method won't be found
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	set_target_properties(
	${PROJECT_NAME}
	PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
	PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:CONSOLE"
	PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE"
	PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:CONSOLE"
	PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(TargetDir)"
	)
endif(MSVC)