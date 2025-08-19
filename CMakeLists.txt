# Nut25 base

cmake_minimum_required(VERSION 3.12)

include(FetchContent)

# Enable hot reload for MSVC if supported
if (POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

cmake_policy(SET CMP0076 NEW)
cmake_policy(SET CMP0079 NEW)

# Get git submodules
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw GIT_TAG master)
FetchContent_MakeAvailable(glfw)


# Project

project("Nut25")


# glad static library

set(glad_SOURCE_DIR "NutLib/vendor/glad")

add_library(glad ${glad_SOURCE_DIR}/src/glad.c)

target_include_directories(glad PRIVATE ${glad_SOURCE_DIR}/include)

# NutLib static library

set(NutLib_SOURCE_DIR "NutLib/src")

add_subdirectory(NutLib)

target_link_directories(NutLib PRIVATE glad glfw)
target_link_libraries(NutLib PRIVATE glad glfw)
target_include_directories(NutLib PRIVATE ${NutLib_SOURCE_DIR} ${glad_SOURCE_DIR}/include ${glfw_SOURCE_DIR}/include)


# Sandbox

add_subdirectory(Sandbox)

target_link_libraries(Sandbox PRIVATE NutLib)
target_include_directories(Sandbox PRIVATE ${NutLib_SOURCE_DIR} ${glad_SOURCE_DIR}/include ${glfw_SOURCE_DIR}/include)
