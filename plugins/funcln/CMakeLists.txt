add_library(funcln SHARED funcln.cpp)

target_include_directories(funcln PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)