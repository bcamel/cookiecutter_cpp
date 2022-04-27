find_package(Catch2 2.3.0 REQUIRED)
include(Catch)
include(CTest)

function({{ cookiecutter.repo_name }}_add_test_exe name)
    add_executable(${ARGV})
    target_link_libraries(${name} PRIVATE Catch2::Catch2 {{ cookiecutter.repo_name }}::{{ cookiecutter.repo_name }})
    catch_discover_tests(${name} TEST_PREFIX ${name}::)
endfunction()

{{ cookiecutter.repo_name }}_add_test_exe({{ cookiecutter.repo_name }}test test-main.cpp test.cpp)