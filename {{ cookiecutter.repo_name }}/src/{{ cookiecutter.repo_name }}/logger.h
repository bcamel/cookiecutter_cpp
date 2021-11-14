#pragma once

#include <spdlog/spdlog.h>

namespace {{ cookiecutter.repo_name }}
{

std::shared_ptr<spdlog::logger> getLogger(const char *name);

}