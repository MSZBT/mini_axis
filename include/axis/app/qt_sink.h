/*
* Заголовочный файл реализации синка для qt
*/

#ifndef QT_SINK_H
#define QT_SINK_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>

#include "axis/app/qt_loggerspace.h"

class QtAppSink : public spdlog::sinks::base_sink<std::mutex> {
private:
    QList<QLoggerSpace*> ui_manager;
public:
    explicit QtAppSink(QList<QLoggerSpace*> ui_manager) : ui_manager(ui_manager) {}
protected:
    void sink_it_(const spdlog::details::log_msg& log_message) override;
    void flush_() override {}
};
#endif
