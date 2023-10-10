add_executable(022 main.cpp)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system REQUIRED)
target_link_libraries(022 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

target_compile_features(022 PUBLIC cxx_std_17)
target_compile_definitions(022 PRIVATE SFML_STATIC)