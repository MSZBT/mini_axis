#include "axis/app/qt_sink.h"
#include "axis/app/qt_loggerspace.h"

QtAppSink::QtAppSink(QList<QLoggerSpace*> ui_manager) : ui_manager(ui_manager) {}

void QtAppSink::register_ui() {
    for (QLoggerSpace* temp : this->ui_manager) {
        temp->register_sink(shared_from_this());
    }
}

void QtAppSink::sink_it_(const spdlog::details::log_msg& log_message) {
    spdlog::level::level_enum level = log_message.level;
    spdlog::memory_buf_t formatted;
    formatter_->format(log_message, formatted);

    emit generate_signal(QString::fromStdString(fmt::to_string(formatted)), level);
}