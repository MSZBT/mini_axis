/*
* Заголовочный файл реализации синка для qt
*/

#ifndef QT_SINK_H
#define QT_SINK_H

#include "axis/app/qt_loggerspace.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>

#include <QObject>

class QLoggerSpace;

class QtAppSink : public QObject,
                  public spdlog::sinks::base_sink<std::mutex>,
                  public std::enable_shared_from_this<QtAppSink> {
    Q_OBJECT
private:
    QList<QLoggerSpace*> ui_manager;
    QString log_buffer[2048];
public:
    explicit QtAppSink(QList<QLoggerSpace*> ui_manager);
    void register_ui();
protected:
    void sink_it_(const spdlog::details::log_msg& log_message) override;
    void flush_() override {}
signals:
    void generate_signal(const QString& log_message, spdlog::level::level_enum level);
};
#endif



