#include "logger.h"

#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace {{ cookiecutter.repo_name }} {

std::shared_ptr<spdlog::logger> getLogger(const char *name) {
  auto logger = spdlog::get(name);
  if (logger) {
    return logger;
  } else {
    return spdlog::stdout_color_mt(name);
  }
}

}