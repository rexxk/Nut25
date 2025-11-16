# NutLib/src

add_library(NutLib STATIC NutLib.h)

set_property(TARGET NutLib PROPERTY CXX_STANDARD 26)

add_subdirectory(Assets)
add_subdirectory(Core)
add_subdirectory(Noise)
add_subdirectory(Renderer)
add_subdirectory(Scene)
add_subdirectory(UI)

target_sources(NutLib PRIVATE

)
