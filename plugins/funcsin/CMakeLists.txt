add_library(funcsin SHARED funcsin.cpp)

target_include_directories(funcsin PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)