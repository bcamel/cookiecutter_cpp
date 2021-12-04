#include "{{ cookiecutter.repo_name }}/logger.hpp"

auto main(int argc, const char* argv[]) -> int
{
    (void)argc;
    (void)argv;
    {{ cookiecutter.repo_name }}::getLogger("main")->info("Hello, world!");
}
