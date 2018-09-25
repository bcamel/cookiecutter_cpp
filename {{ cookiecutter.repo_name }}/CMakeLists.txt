cmake_minimum_required(VERSION 3.12)

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project({{ cookiecutter.repo_name }}
    VERSION 0.0.1
    LANGUAGES C CXX
    DESCRIPTION "{{ cookiecutter.project_short_description }}"
    )

if(NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
endif()

include(ClangTidy)

# Ensure Conan deps are up-to-date
find_package(Conan)
if(Conan_FOUND)
    conan_install()
endif()

# Import the deps that were setup by Conan
find_package(spdlog 1.1.0 REQUIRED)

# Include embedded third-party components we need for the build
add_subdirectory(external)

if(NOT MSVC)
    add_compile_options(-Wall -Wextra)
    if(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        add_compile_options(-Werror)
    endif()
endif()

add_subdirectory(src)

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    enable_testing()
    add_subdirectory(tests)
endif()

option(BUILD_EXAMPLES "Build examples" ON)
if(BUILD_EXAMPLES AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    add_subdirectory(examples)
endif()

add_subdirectory(extras)
