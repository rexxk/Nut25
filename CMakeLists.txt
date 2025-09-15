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

FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm GIT_TAG master)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(stbimage GIT_REPOSITORY https://github.com/nothings/stb GIT_TAG master)
FetchContent_MakeAvailable(stbimage)

FetchContent_Declare(imgui GIT_REPOSITORY https://github.com/ocornut/imgui GIT_TAG docking)
FetchContent_MakeAvailable(imgui)

# Project

project("Nut25")


# glad static library

set(glad_SOURCE_DIR "NutLib/vendor/glad")

add_library(glad ${PROJECT_SOURCE_DIR}/${glad_SOURCE_DIR}/src/glad.c)

target_include_directories(glad PRIVATE ${glad_SOURCE_DIR}/include)

# imgui static library

add_library(imgui ${imgui_SOURCE_DIR}/imgui.cpp
				  ${imgui_SOURCE_DIR}/imgui_demo.cpp
				  ${imgui_SOURCE_DIR}/imgui_draw.cpp
				  ${imgui_SOURCE_DIR}/imgui_tables.cpp
				  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
				  ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
				  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PRIVATE ${imgui_SOURCE_DIR} ${glfw_SOURCE_DIR}/include)

# NutLib static library

set(NutLib_SOURCE_DIR "NutLib/src")

add_subdirectory(NutLib)

target_link_directories(NutLib PRIVATE glad glfw imgui)
target_link_libraries(NutLib PRIVATE glad glfw imgui)
target_include_directories(NutLib PRIVATE ${NutLib_SOURCE_DIR} ${glad_SOURCE_DIR}/include ${glfw_SOURCE_DIR}/include ${glm_SOURCE_DIR} ${stbimage_SOURCE_DIR} ${imgui_SOURCE_DIR})


# Sandbox

add_subdirectory(Sandbox)

set_property(TARGET Sandbox PROPERTY DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Sandbox")

target_link_libraries(Sandbox PRIVATE NutLib)
target_include_directories(Sandbox PRIVATE ${NutLib_SOURCE_DIR} ${glad_SOURCE_DIR}/include ${glfw_SOURCE_DIR}/include ${glm_SOURCE_DIR} ${stbimage_SOURCE_DIR} ${imgui_SOURCE_DIR})
