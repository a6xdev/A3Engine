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
)

target_compile_definitions(a3-lib PRIVATE A3_EXPORT)

target_include_directories(a3-lib PUBLIC ${A3_INCLUDE_DIRS})
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

# ---- A3 Editor Executable ----
add_executable(a3-editor 
    "src/editor/Editor.cpp"
    "src/editor/Main.cpp"
)

target_link_libraries(a3-editor PRIVATE a3-lib)
target_include_directories(a3-editor PRIVATE ${A3_INCLUDE_DIRS} )
copy_shaders(a3-editor)

# ---- A3 Game Executable ----
add_executable(a3-game "src/runtime/Game.cpp")

target_link_libraries(a3-game PRIVATE a3-lib)
target_include_directories(a3-game PRIVATE ${A3_INCLUDE_DIRS} )
copy_shaders(a3-game)
