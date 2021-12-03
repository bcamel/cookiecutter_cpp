#include "{{ cookiecutter.repo_name }}/logger.h"
#include <spdlog/sinks/stdout_color_sinks-inl.h>

namespace {{ cookiecutter.repo_name }}
{

std::shared_ptr<spdlog::logger> getLogger(const char* name)
{
    if (auto logger = spdlog::get(name))
    {
        return logger;
    }
    else
    {
        return spdlog::stdout_color_mt(name);
    }
}

} // namespace {{ cookiecutter.repo_name }}