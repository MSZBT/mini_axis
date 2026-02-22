/*
* Заголовочный файл для реализации логгера
*/

#ifndef AXIS_TEST_LOCAL_LOGGER_H
#define AXIS_TEST_LOCAL_LOGGER_H

#include "spdlog/logger.h"
#include <spdlog/sinks/base_sink.h>

#include <memory>
#include <string>


class LocalLogger {
private:
    std::shared_ptr<spdlog::logger> m_logger;
public:
    LocalLogger();

    void registerSink(std::shared_ptr<spdlog::sinks::sink> sink);

    void info(const std::string& msg);
    void warn(const std::string& msg);
    void error(const std::string& msg);
};

#endif //AXIS_TEST_LOCAL_LOGGER_H