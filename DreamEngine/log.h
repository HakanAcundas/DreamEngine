#pragma once
#include <spdlog/spdlog.h>

#define DREAM_LOG_TAG_TRACE(tag, ...)    spdlog::default_logger()->trace      ("[{}] {}", tag, fmt::format(__VA_ARGS__))
#define DREAM_LOG_TAG_DEBUG(tag, ...)    spdlog::default_logger()->debug      ("[{}] {}", tag, fmt::format(__VA_ARGS__))
#define DREAM_LOG_TAG_INFO(tag, ...)     spdlog::default_logger()->info       ("[{}] {}", tag, fmt::format(__VA_ARGS__))
#define DREAM_LOG_TAG_WARN(tag, ...)     spdlog::default_logger()->warn       ("[{}] {}", tag, fmt::format(__VA_ARGS__))
#define DREAM_LOG_TAG_ERROR(tag, ...)    spdlog::default_logger()->error      ("[{}] {}", tag, fmt::format(__VA_ARGS__))
#define DREAM_LOG_TAG_FATAL(tag, ...)    spdlog::default_logger()->critical   ("[{}] {}", tag, fmt::format(__VA_ARGS__))
