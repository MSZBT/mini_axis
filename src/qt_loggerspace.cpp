#include "axis/app/qt_loggerspace.h"
#include <axis/app/qt_sink.h>

#include <QWidget>
#include <QTimer>

QLoggerSpace::QLoggerSpace() {
    setPlainText("Отслеживание логов\n");
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAlignment(Qt::AlignBottom);
    setReadOnly(true);


    setStyleSheet(
        "QTextEdit {"
        "    font-size: 24px;"
        "}"
    );

    /*буфер для логов*/
    log_buffer.reserve(2048);

    /*Таймер по выводу логов*/
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QLoggerSpace::show_logs);
    timer->start(1000);
}

void QLoggerSpace::register_sink(std::shared_ptr<QtAppSink> qt_sink) {
    this->sink_qt = qt_sink;

    QObject::connect(this->sink_qt.get(), &QtAppSink::generate_signal, this, &QLoggerSpace::fill_buffer);
}

void QLoggerSpace::show_logs() {
    for (const auto& msg : log_buffer) {
        if (!msg.isEmpty()) {
            this->append(msg);
        }
    }
    this->log_buffer.clear();
}

void QLoggerSpace::fill_buffer(const QString& log_message, spdlog::level::level_enum level) {
    static std::map<spdlog::level::level_enum, std::string> colorMap = {
        {spdlog::level::trace, "gray"},
        {spdlog::level::debug, "white"},
        {spdlog::level::info, "green"},
        {spdlog::level::warn, "yellow"},
        {spdlog::level::err, "red"},
        {spdlog::level::critical, "red"}
    };

    auto tmp = colorMap.find(level);
    std::string color = (tmp != colorMap.end()) ? tmp->second : "white";

    //append(QString("<font color=\"%1\">%2</font>").arg(color).arg(log_message));
    this->log_buffer.append(QString("<font color=\"%1\">%2</font>").arg(color).arg(log_message));
    //moveCursor(QTextCursor::End);
}