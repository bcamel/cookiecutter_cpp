cmake_minimum_required(VERSION 3.12)

project({{ cookiecutter.repo_name }}
    VERSION {{ cookiecutter.project_version }}
    LANGUAGES C CXX
    DESCRIPTION "{{ cookiecutter.project_short_description }}"
    )

# Add custom cmake includes
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# Add cmake includes fetched by package manager
list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}")    

include(GNUInstallDirs)
include(conan)

# Define the minimum C++ standard that is required
if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD {{ cookiecutter.cxx_minimum_standard }})
elseif(CMAKE_CXX_STANDARD LESS {{ cookiecutter.cxx_minimum_standard }})
    message(FATAL_ERROR "Please specify CMAKE_CXX_STANDARD of {{ cookiecutter.cxx_minimum_standard }} or higher")
endif()

if (NOT DEFINED CMAKE_CXX_STANDARD_REQUIRED)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

# Avoid use of compiler language extensions
if (NOT DEFINED CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS FALSE)
endif()

if(NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

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
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
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
