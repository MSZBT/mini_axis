/*
* Заголовочный файл с описанием работы поля выводов
*/

#ifndef AXIS_TEST_QT_LOGGERSPACE_H
#define AXIS_TEST_QT_LOGGERSPACE_H

#include <QTextEdit>
#include <QString>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>


class QtAppSink;

class QLoggerSpace : public QTextEdit {
private:
    std::shared_ptr<QtAppSink> sink_qt;

public:
    QLoggerSpace();

    void register_sink(std::shared_ptr<QtAppSink> sink);

/*Публично дает вохможность обрабатывать сигналы*/
private slots:
    void outLogs(const QString& log_message, spdlog::level::level_enum level);
};

#endif //AXIS_TEST_QT_LOGGERSPACE_H