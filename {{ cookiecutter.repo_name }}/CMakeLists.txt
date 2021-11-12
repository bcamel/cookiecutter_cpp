cmake_minimum_required(VERSION 3.12)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")

project({{ cookiecutter.repo_name }}
    VERSION {{ cookiecutter.project_version }}
    LANGUAGES C CXX
    DESCRIPTION "{{ cookiecutter.project_short_description }}"
    )

# Initialize some default paths
include(GNUInstallDirs)

# Define the minimum C++ standard that is required
set(CMAKE_CXX_STANDARD {{ cookiecutter.cxx_minimum_standard }})
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
endif()

include(ClangTidy)

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/develop/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                TLS_VERIFY ON)
  include(${CMAKE_BINARY_DIR}/conan.cmake)
else()
    message(STATUS "Found conan.cmake in ${CMAKE_CURRENT_SOURCE_DIR}/cmake")
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/conan.cmake")
endif()

conan_cmake_autodetect(settings)

conan_cmake_configure(REQUIRES                       
                      fmt/8.0.1
                      spdlog/1.9.2
                      catch2/2.13.7
                      GENERATORS
                      cmake_find_package)

conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conancenter
                    SETTINGS ${settings})

# Include embedded third-party components we need for the build
add_subdirectory(external)

find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(Catch2 REQUIRED)

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

# This prints a summary of found dependencies
include(FeatureSummary)
feature_summary(WHAT ALL)
