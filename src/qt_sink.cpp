#include "axis/app/qt_sink.h"

void QtAppSink::sink_it_(const spdlog::details::log_msg& log_message) {
    spdlog::level::level_enum level = log_message.level;
    spdlog::memory_buf_t formatted;
    formatter_->format(log_message, formatted);

    for (const auto& log_space_tmp : this->ui_manager) {
        if (log_space_tmp) {
            log_space_tmp->outLogs(fmt::to_string(formatted), level);
        }
    }
}