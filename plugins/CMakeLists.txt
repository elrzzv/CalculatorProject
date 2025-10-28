if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/funcsin.cpp")
    add_library(funcsin SHARED "${CMAKE_CURRENT_SOURCE_DIR}/funcsin.cpp")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/funccos.cpp")
    add_library(funccos SHARED "${CMAKE_CURRENT_SOURCE_DIR}/funccos.cpp")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/funcln.cpp")
    add_library(funcln SHARED "${CMAKE_CURRENT_SOURCE_DIR}/funcln.cpp")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/funcdeg.cpp")
    add_library(funcdeg SHARED "${CMAKE_CURRENT_SOURCE_DIR}/funcdeg.cpp")
endif()


# Для Windows
if(WIN32)
    target_compile_definitions(funcsin PRIVATE BUILDING_DLL=1)
    target_compile_definitions(funccos PRIVATE BUILDING_DLL=1)
    target_compile_definitions(funcln PRIVATE BUILDING_DLL=1)
    target_compile_definitions(funcdeg PRIVATE BUILDING_DLL=1)
endif()