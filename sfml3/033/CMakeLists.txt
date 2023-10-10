add_executable(033 main.cpp)

target_include_directories(033 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(033 PUBLIC cxx_std_17)
target_compile_definitions(033 PRIVATE SFML_STATIC)

target_link_libraries(033 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})