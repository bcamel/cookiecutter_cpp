add_library(lib{{ cookiecutter.repo_name }}
    {{ cookiecutter.repo_name }}/logger.cpp
    )
set_property(TARGET lib{{ cookiecutter.repo_name }} PROPERTY OUTPUT_NAME {{ cookiecutter.repo_name }})
add_library({{ cookiecutter.repo_name }}::{{ cookiecutter.repo_name }} ALIAS lib{{ cookiecutter.repo_name }})
target_include_directories(
    lib{{ cookiecutter.repo_name }}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    ${CMAKE_SOURCE_DIR}/include
    )
target_link_libraries(lib{{ cookiecutter.repo_name }}
    PUBLIC
        spdlog::spdlog
    )

add_executable({{ cookiecutter.repo_name }} main.cpp)
target_link_libraries({{ cookiecutter.repo_name }} PRIVATE
    {{ cookiecutter.repo_name }}::{{ cookiecutter.repo_name }}
    )

set_property(TARGET lib{{ cookiecutter.repo_name }} PROPERTY CXX_STANDARD 17)
set_property(TARGET {{ cookiecutter.repo_name }} PROPERTY CXX_STANDARD 17)
