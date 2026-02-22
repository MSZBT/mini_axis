/*
* Заголовочный файл с описанием работы поля выводов
*/

#ifndef AXIS_TEST_QT_LOGGERSPACE_H
#define AXIS_TEST_QT_LOGGERSPACE_H

#include <QTextEdit>
#include <spdlog/spdlog.h>



#include <string>

class QLoggerSpace : public QTextEdit {
public:
    QLoggerSpace();

    void outLogs(const std::string& log_message, spdlog::level::level_enum level);
};

#endif //AXIS_TEST_QT_LOGGERSPACE_H