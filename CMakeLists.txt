# thanks aplok (Twitter/X: @GabrielAplok)
cmake_minimum_required(VERSION 3.28)

project(a3-engine
    VERSION 0.1.0
    LANGUAGES C CXX
    DESCRIPTION "A3 Game Engine"
)

# ---- Language Standards ----
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# ---- vcpkg Toolchain ----
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
else()
    message(FATAL_ERROR "VCPKG_ROOT environment variable not set. Please set it to your vcpkg installation directory.")
endif()

# ---- Find Packages ----
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(Jolt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# ---- Include Directories ----
set(A3_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/src # Yea, I will include the header files in the same location as the source code files.
)

# ---- A3 Core Library ----
add_library(a3-lib SHARED
    "src/engine/Core.cpp"
    "src/engine/Engine.cpp"
    "src/engine/Renderer.cpp"
    "src/engine/ImGuiLayer.cpp"
    "src/engine/input/Input.cpp"

    # Assets
    "src/engine/assets/asset.cpp"
    "src/engine/assets/Texture2D.cpp"

    # External
    "src/engine/external/stb/stb_image.cpp"
    "src/engine/external/stb/stb_image_write.cpp"
)

target_compile_definitions(a3-lib PRIVATE A3_EXPORT)

target_include_directories(a3-lib 
    PUBLIC ${A3_INCLUDE_DIRS}
    PRIVATE "src/engine/external"
)
target_compile_definitions(a3-lib PRIVATE GLM_ENABLE_EXPERIMENTAL)
target_compile_features(a3-lib PUBLIC cxx_std_23)

target_link_libraries(a3-lib
    PUBLIC glad::glad
	PUBLIC glfw
    PUBLIC glm::glm
	PUBLIC imgui::imgui
	PUBLIC Jolt::Jolt
	PUBLIC nlohmann_json::nlohmann_json
)

target_precompile_headers(a3-lib PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/engine/pch.h")

# ---- Helper: Copy shaders to output directory ----
function(copy_shaders TARGET_NAME)
    set(SHADER_SOURCE_DIR "${CMAKE_SOURCE_DIR}/shader")
    set(SHADER_DEST_DIR "$<TARGET_FILE_DIR:${TARGET_NAME}>/shader")

    add_custom_command(
        TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${SHADER_DEST_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${SHADER_SOURCE_DIR}"
                "${SHADER_DEST_DIR}"
        COMMENT "Copying shaders to ${SHADER_DEST_DIR}"
        VERBATIM
    )
endfunction()

# ------------------------------
# ---- A3 Editor Executable ----
# ------------------------------

add_executable(a3-editor 
    "src/editor/Main.cpp"
    "src/editor/EditorPanel.cpp"
    "src/editor/EditorContext.cpp"
    "src/editor/panels/AssetBrowser.cpp"
 "src/editor/IconsLibrary.cpp")

set_target_properties(a3-editor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/editor"
)

add_custom_command(TARGET a3-editor POST_BUILD
# Copy a3-ib
    COMMAND ${CMAKE_COMMAND} -E copy 
        "$<TARGET_FILE:a3-lib>" 
        "$<TARGET_FILE_DIR:a3-editor>"

# Make Assets Dir
    COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:a3-editor>/assets"

# Copy assets to build dir
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/src/editor/assets"
        "$<TARGET_FILE_DIR:a3-editor>/assets"
)

target_link_libraries(a3-editor PRIVATE a3-lib)
target_include_directories(a3-editor PRIVATE ${A3_INCLUDE_DIRS} )
copy_shaders(a3-editor)

target_compile_definitions(a3-editor PRIVATE 
    A3_PROJECT_ROOT="${A3_INCLUDE_DIRS}"
)

# ----------------------------
# ---- A3 Game Executable ----
# ----------------------------
add_executable(a3-game 
    "src/runtime/Game.cpp"
)

set_target_properties(a3-game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/game"
)

add_custom_command(TARGET a3-game POST_BUILD
# Copy a3-ib
    COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_FILE:a3-lib>" 
        "$<TARGET_FILE_DIR:a3-game>"

# Make Assets Dir
    COMMAND ${CMAKE_COMMAND} -E make_directory 
        "$<TARGET_FILE_DIR:a3-editor>/assets"

# Copy assets to build dir
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/src/editor/assets"
        "$<TARGET_FILE_DIR:a3-editor>/assets"
)

target_link_libraries(a3-game PRIVATE a3-lib)
target_include_directories(a3-game PRIVATE ${A3_INCLUDE_DIRS} )
copy_shaders(a3-game)