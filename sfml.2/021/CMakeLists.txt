add_executable(021 main.cpp)

target_include_directories(021 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(021 PUBLIC cxx_std_17)
target_compile_definitions(021 PRIVATE SFML_STATIC)

target_link_libraries(021 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})