add_executable(031 main.cpp)

target_include_directories(031 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(031 PUBLIC cxx_std_17)
target_compile_definitions(031 PRIVATE SFML_STATIC)

target_link_libraries(031 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})