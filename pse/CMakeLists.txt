file(GLOB pseSrc *.cpp *.hpp)
add_library(pse STATIC ${pseSrc})
target_include_directories(pse PUBLIC .)

putils_conan(sfml/2.5.1@bincrafters/stable)
target_link_libraries(pse PUBLIC putils CONAN_PKG::sfml)