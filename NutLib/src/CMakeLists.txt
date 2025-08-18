# NutLib/src

add_library(NutLib STATIC NutLib.h)

set_property(TARGET NutLib PROPERTY CXX_STANDARD 26)

add_subdirectory(Core)


target_sources(NutLib PRIVATE
	EntryPoint.h
)
