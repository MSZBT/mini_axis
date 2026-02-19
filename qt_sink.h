#ifndef QT_sink_H
#define QT_sink_H


#include <QApplication>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <QString>
#include <QPushButton>

#include <string>
#include <memory>
#include <iostream>
#include <vector>

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/base_sink.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/logger.h"


class QLoggerSpace;

class AppSink : public spdlog::sinks::base_sink<std::mutex> {
protected:
    void sink_it_(const spdlog::details::log_msg& log_message) override;
    void flush_() override {}
};

#endif