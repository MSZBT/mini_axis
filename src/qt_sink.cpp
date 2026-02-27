#include "axis/app/qt_sink.h"
#include "axis/app/qt_loggerspace.h"

void QtAppSink::sink_it_(const spdlog::details::log_msg& log_message) {
    spdlog::level::level_enum level = log_message.level;
    spdlog::memory_buf_t formatted;
    formatter_->format(log_message, formatted);

    emit generate_signal(QString::fromStdString(fmt::to_string(formatted)), level);
}