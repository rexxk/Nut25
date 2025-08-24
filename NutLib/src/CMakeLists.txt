# NutLib/src

add_library(NutLib STATIC NutLib.h)

set_property(TARGET NutLib PROPERTY CXX_STANDARD 26)

add_subdirectory(Core)
add_subdirectory(Events)
add_subdirectory(Renderer)


target_sources(NutLib PRIVATE
	EntryPoint.h
)
