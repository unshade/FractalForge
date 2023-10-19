cmake_minimum_required(VERSION 3.10)
project(FractalForge)

# Définir le mode par défaut à Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Spécifier la version C++ requise
set(CMAKE_CXX_STANDARD 11)

# Ajouter des dossiers d'inclusion
include_directories(/opt/homebrew/Cellar/sfml/2.6.0/include)
include_directories(include)

# Ajouter des dossiers de liens
link_directories(/opt/homebrew/Cellar/sfml/2.6.0/lib)

# Liste des fichiers sources
file(GLOB SOURCES "src/*.cpp"
        "src/fractals/*.cpp"
        "include/imgui.cpp"
        "include/imgui_draw.cpp"
        "include/imgui_widgets.cpp"
        "include/imgui_tables.cpp"
        "include/imgui_demo.cpp"
        "include/imgui-SFML.cpp")

# Créer un exécutable
add_executable(FractalForge ${SOURCES})

# Liens des bibliothèques
target_link_libraries(FractalForge sfml-graphics sfml-window sfml-system sfml-audio sfml-network)

# Copier le fichier mandelbrot dans le répertoire de construction
add_custom_target(copy_shader ALL
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/shaders/julia.glsl
        ${CMAKE_BINARY_DIR}/shaders/julia.glsl
        DEPENDS ${CMAKE_SOURCE_DIR}/shaders/julia.glsl)

# Ajouter une dépendance à l'exécutable pour copier le shader lorsque le fichier est modifié
add_dependencies(FractalForge copy_shader)



if(APPLE)
    # Sur macOS, ajouter des frameworks supplémentaires
    find_library(OPENGL_LIBRARY OpenGL)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation)
    find_library(FOUNDATION_LIBRARY Foundation)
    find_library(COCOA_LIBRARY Cocoa)

    target_link_libraries(FractalForge ${OPENGL_LIBRARY} ${COREFOUNDATION_LIBRARY} ${FOUNDATION_LIBRARY} ${COCOA_LIBRARY})
else()
    target_link_libraries(FractalForge GL)
endif()
