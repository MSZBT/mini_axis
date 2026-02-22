#include "axis/app/local_logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include <vector>

LocalLogger::LocalLogger() {
    std::vector<spdlog::sink_ptr> sinks;

    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    sinks.push_back(consoleSink);

    m_logger = std::make_shared<spdlog::logger>("multi_logger", sinks.begin(), sinks.end());
    spdlog::register_logger(m_logger);
    m_logger->set_level(spdlog::level::info);
    m_logger->info("Logger initialized");
}

void LocalLogger::registerSink(std::shared_ptr<spdlog::sinks::sink> sink) {
    if (m_logger) {
        m_logger->sinks().push_back(sink);
    }
}

void LocalLogger::info(const std::string& msg) { m_logger->info(msg); }
void LocalLogger::warn(const std::string& msg) { m_logger->warn(msg); }
void LocalLogger::error(const std::string& msg) { m_logger->error(msg); }