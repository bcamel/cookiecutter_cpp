#include <{{ cookiecutter.repo_name }}/logger.h>

int main(int argc, const char *argv[]) {
  (void)(argc);
  (void)(argv);
  {{ cookiecutter.repo_name }}::getLogger("main")->info("Hello, world!");
}