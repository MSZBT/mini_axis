/*
* Заголовочный файл с описанием работы поля выводов
*/

#ifndef AXIS_TEST_QT_LOGGERSPACE_H
#define AXIS_TEST_QT_LOGGERSPACE_H

#define STRING_LIMITOR 5

#include <QTextEdit>
#include <QString>
#include <QTimer>
#include <QTextDocument>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>


class QtAppSink;

class QLoggerSpace : public QTextEdit {
    Q_OBJECT
private:
    std::shared_ptr<QtAppSink> sink_qt;
    QTimer *timer;
    QString log_buffer;
    int cut_strings = 0;

public:
    QLoggerSpace();

    void register_sink(std::shared_ptr<QtAppSink> sink);
    void show_logs();

private slots:
    void fill_buffer(const QString& log_message, spdlog::level::level_enum level);
};

#endif //AXIS_TEST_QT_LOGGERSPACE_H