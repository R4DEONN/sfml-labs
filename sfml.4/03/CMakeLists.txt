add_executable(03 main.cpp)

target_include_directories(03 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(03 PUBLIC cxx_std_17)
target_compile_definitions(03 PRIVATE SFML_STATIC)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(03 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})