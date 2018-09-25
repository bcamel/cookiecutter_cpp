find_package(Catch2 2.3.0 REQUIRED)
include(Catch)

add_library({{ cookiecutter.repo_name }}-test-lib STATIC test-main.cpp
test.cpp
)

target_link_libraries({{ cookiecutter.repo_name }}-test-lib PUBLIC Catch2::Catch2 {{ cookiecutter.repo_name }}::{{ cookiecutter.repo_name }})

set_property(TARGET {{ cookiecutter.repo_name }}-test-lib PROPERTY CXX_STANDARD 17)

function({{ cookiecutter.repo_name }}_add_test_exe name)
    add_executable(${ARGV})
    target_link_libraries(${name} PRIVATE {{ cookiecutter.repo_name }}-test-lib)
    catch_discover_tests(${name} TEST_PREFIX ${name}::)
endfunction()

{{ cookiecutter.repo_name }}_add_test_exe(testtest test.cpp)