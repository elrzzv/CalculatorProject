#все файлы плагинов
file(GLOB PLUGIN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/func*.cpp")

set(PLUGIN_TARGETS "")

foreach(PLUGIN_SOURCE ${PLUGIN_SOURCES})
    get_filename_component(PLUGIN_TARGET ${PLUGIN_SOURCE} NAME_WE)
    add_library(${PLUGIN_TARGET} SHARED ${PLUGIN_SOURCE})
    list(APPEND PLUGIN_TARGETS ${PLUGIN_TARGET})
    message(STATUS "Added plugin: ${PLUGIN_TARGET}")
endforeach()

#для windows
if(WIN32)
    foreach(PLUGIN_TARGET ${PLUGIN_TARGETS})
        target_compile_definitions(${PLUGIN_TARGET} PRIVATE BUILDING_DLL=1)
    endforeach()
endif()

#cохраняем список для использования в главном CMakeLists.txt
set(PLUGIN_TARGETS ${PLUGIN_TARGETS} PARENT_SCOPE)