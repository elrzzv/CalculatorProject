add_library(funcdeg SHARED funcdeg.cpp)

target_include_directories(funcdeg PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)