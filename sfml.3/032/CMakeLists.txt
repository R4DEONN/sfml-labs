add_executable(032 main.cpp)

target_include_directories(032 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(032 PUBLIC cxx_std_17)
target_compile_definitions(032 PRIVATE SFML_STATIC)

target_link_libraries(032 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})