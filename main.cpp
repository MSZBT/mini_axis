//#include "axis/apps/qt_app.h" //вывод функционала наружу
//
//#include "axis/core" //подключение core чтобы использовать логгер


#include <QApplication>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <memory>
#include <QString>
#include <QPushButton>
#include <format>
#include <string>

#include <iostream>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/base_sink.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/async.h"
#include "spdlog/logger.h"
/*МЕНЯТЬ ПУТИ НА ОТНОСИТЕЛЬНЫЕ*/

void qtLogSent(const std::string& log_message, int level);

/*РЕАЛИЗАЦИЯ ЛОГГЕРА ДЛЯ ТЕСТИРОВАНИЯ*/

class Logger {
private:
    std::shared_ptr<spdlog::logger> m_logger;

public:
    Logger() {
        std::vector<spdlog::sink_ptr> sinks;

        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        sinks.push_back(consoleSink);

        m_logger = std::make_shared<spdlog::logger>("multi_logger", sinks.begin(), sinks.end());
        spdlog::register_logger(m_logger);
        m_logger->set_level(spdlog::level::info);
        m_logger->info("Logger initialized");
    }

    std::shared_ptr<spdlog::logger> getSpdlogLogger() {
        return m_logger;
    }

    void registerSink(std::shared_ptr<spdlog::sinks::sink> sink) {
        if (m_logger) {
            m_logger->sinks().push_back(sink);
        }
    }

    void info(const std::string& msg) { m_logger->info(msg); }
    void warn(const std::string& msg) { m_logger->warn(msg); }
    void error(const std::string& msg) { m_logger->error(msg); }
};


auto logger = std::make_shared<Logger>();

class AppSink : public spdlog::sinks::base_sink<std::mutex> {
protected:
    void sink_it_(const spdlog::details::log_msg& log_message) override {
        spdlog::level::level_enum level = log_message.level;
        spdlog::memory_buf_t formatted;
        formatter_->format(log_message, formatted);

        qtLogSent(fmt::to_string(formatted), level);
    }

    void flush_() override {}
};


/*класс для поля выввода логов*/
class QLoggerSpace : public QTextEdit {
private:
    //std::shared_ptr<Logger> logger;
    std::shared_ptr<AppSink> personalSink;

public:
    QLoggerSpace() {
        setPlainText("Отслеживание логов\n");
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setAlignment(Qt::AlignBottom);
        setReadOnly(true);

        setStyleSheet(
            "QTextEdit {"
            "    font-size: 24px;"
            "}"
        );

        //logger = Logger::getSpdlogLogger();

    }

    void openSink() {
        try {
            if (logger != nullptr) {
                personalSink = std::make_shared<AppSink>();
                logger->registerSink(personalSink);
            }
        } catch (const std::exception& e) {
            std::cout << "Error with sink opening" << std::endl;
            return;
        }
    }

    std::shared_ptr<AppSink> getSink() {
        return personalSink;
    }

    void outLogs(const QString& add_data, std::string color) {
        append(QString::fromStdString(std::format("<font color=\"{}\">{}</font>", color, add_data.toStdString())));
        moveCursor(QTextCursor::End);
    }
};

/*Объект поля логов*/
std::shared_ptr<QLoggerSpace> log_space;

void qtLogSent(const std::string& log_message, int level) {
    std::string color = "white";
    switch (level) {
        case spdlog::level::trace: {
            color = "gray";
            break;
        }
        case spdlog::level::debug: {
            color = "white";
            break;
        }
        case spdlog::level::info: {
            color = "green";
            break;
        }
        case spdlog::level::warn: {
            color = "yellow";
            break;
        }
        case spdlog::level::err: {
            color = "red";
            break;
        }
        case spdlog::level::critical: {
            color = "red";
            break;
        }
        case spdlog::level::off:
            break;
    }
    log_space->outLogs(QString::fromStdString(log_message), color);
}



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    QWidget window;
    window.setWindowTitle("Logger");
    window.setStyleSheet("QWidget { background-color: #1a1a1a; min-width: 450px; min-height: 300px; }");

    log_space = std::make_shared<QLoggerSpace>();

    auto scrollArea = std::make_shared<QScrollArea>();
    scrollArea->setWidget(log_space.get());
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { border: none; }");


    auto virtual_box = std::make_shared<QVBoxLayout>();
    virtual_box->addWidget(scrollArea.get());
    virtual_box->setContentsMargins(10, 5, 10, 0);

    QPushButton *test = new QPushButton("Press", &window);

    //QObject::connect(test, &QPushButton::clicked, [log_space]() { log_space->appendText("moew", 1);}); - отправить сообещение через логгер
    virtual_box->addWidget(test);

    window.setLayout(virtual_box.get());
    window.show();

    log_space->openSink();

    /*ТЕСТИРОВАНИЕ В ВИДЕ НАПИСАНИЯ СОБСВЕННОГО ЛОГГЕРА ЛОКАЛЬНО*/
    return app.exec();
}

