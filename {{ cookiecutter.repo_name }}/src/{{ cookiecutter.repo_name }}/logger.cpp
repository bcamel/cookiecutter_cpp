#include "{{ cookiecutter.repo_name }}/logger.hpp"

#include "spdlog/sinks/stdout_color_sinks-inl.h"

namespace {{ cookiecutter.repo_name }}
{

auto getLogger(const char* name) -> std::shared_ptr<spdlog::logger>
{
    if (auto logger = spdlog::get(name))
    {
        return logger;
    }
    return spdlog::stdout_color_mt(name);
}

} // namespace {{ cookiecutter.repo_name }}