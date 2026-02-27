#include "axis/app/qt_loggerspace.h"
#include <axis/app/qt_sink.h>

#include <QWidget>
#include <QTimer>
#include <QTextCursor>



QLoggerSpace::QLoggerSpace(std::shared_ptr<QtAppSink> qt_sink) : sink_qt(qt_sink) {
    setPlainText("Отслеживание логов\n");
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setAlignment(Qt::AlignBottom);
    setReadOnly(true);


    setStyleSheet(
        "QTextEdit {"
        "    font-size: 24px;"
        "}"
    );

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QLoggerSpace::show_logs);
    timer->start(1000);

    QObject::connect(this->sink_qt.get(), &QtAppSink::generate_signal, this, &QLoggerSpace::fill_buffer);
}


void QLoggerSpace::show_logs() {
    if (!log_buffer.isEmpty()) {
        this->append(log_buffer);

        QTextDocument *doc = document();
        QTextCursor cursor(doc);

        int blockCount = doc->blockCount();

        if (blockCount > STRING_LIMITOR) {
            cursor.movePosition(QTextCursor::Start);

            for(int i = 0; i < blockCount - STRING_LIMITOR; ++i) {
                cursor.movePosition(QTextCursor::NextBlock);
                cursor.movePosition(QTextCursor::StartOfBlock);
            }

            cursor.movePosition(QTextCursor::StartOfBlock);
            cursor.setPosition(0, QTextCursor::KeepAnchor);
            cursor.removeSelectedText();
            cursor.deleteChar();
        }

        log_buffer.clear();
    }
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

    this->log_buffer.append(QString("<font color=\"%1\">%2</font><br>").arg(color, log_message.trimmed()));
}