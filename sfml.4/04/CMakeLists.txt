add_executable(04 main.cpp)

target_include_directories(04 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(04 PUBLIC cxx_std_17)
target_compile_definitions(04 PRIVATE SFML_STATIC)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(04 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})