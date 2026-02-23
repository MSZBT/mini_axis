/*
* Заголовочный файл с описанием работы поля выводов
*/

#ifndef AXIS_TEST_QT_LOGGERSPACE_H
#define AXIS_TEST_QT_LOGGERSPACE_H

#include <QTextEdit>
#include <QString>
#include <QObject>
#include <QTimer>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>


class QtAppSink;

class QLoggerSpace : public QTextEdit  {
    Q_OBJECT
private:
    std::shared_ptr<QtAppSink> sink_qt;
    QTimer *timer;
    QVector<QString> log_buffer;

public:
    QLoggerSpace();

    void register_sink(std::shared_ptr<QtAppSink> sink);
    void show_logs();
/*Публично дает вохможность обрабатывать сигналы*/
private slots:
    void fill_buffer(const QString& log_message, spdlog::level::level_enum level);
};

#endif //AXIS_TEST_QT_LOGGERSPACE_H