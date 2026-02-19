//#include "axis/core" //подключение core чтобы использовать логгер/синглтон

#include "qt_sink.h"


class Logger;
class QLoggerSpace;
class AppSink;

extern std::shared_ptr<Logger> logger;
extern QLoggerSpace* log_space;
extern QList<QLoggerSpace*> logs_objects;



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



class QLoggerSpace : public QTextEdit {
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
    }

    void outLogs(const std::string& log_message, spdlog::level::level_enum level) {
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

        append(QString("<font color=\"%1\">%2</font>").arg(color).arg(log_message));
        moveCursor(QTextCursor::End);
    }
};

QList<QLoggerSpace*> logs_objects;

/*Объект поля логов*/
QLoggerSpace* log_space;
QLoggerSpace* log_space2;




/*РЕАЛИЗАЦИЯ СИНКА*/
void AppSink::sink_it_(const spdlog::details::log_msg& log_message) {
    spdlog::level::level_enum level = log_message.level;
    spdlog::memory_buf_t formatted;
    formatter_->format(log_message, formatted);

    for (const auto& log_space_tmp : logs_objects) {
        if (log_space_tmp) {
            log_space_tmp->outLogs(fmt::to_string(formatted), level);
        }
    }
}



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    QWidget window;
    window.setWindowTitle("Logger");
    window.setStyleSheet("QWidget { background-color: #1a1a1a; min-width: 450px; min-height: 300px; }");


    log_space = new QLoggerSpace();
    log_space2 = new QLoggerSpace();

    auto scrollArea = new QScrollArea();
    scrollArea->setWidget(log_space);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { border: none; }");

    auto scrollArea2 = new QScrollArea();
    scrollArea2->setWidget(log_space2);
    scrollArea2->setWidgetResizable(true);
    scrollArea2->setStyleSheet("QScrollArea { border: none; }");

    logs_objects.push_back(log_space);
    logs_objects.push_back(log_space2);

    auto virtual_box = new QVBoxLayout();
    virtual_box->addWidget(scrollArea);
    virtual_box->addWidget(scrollArea2);
    virtual_box->setContentsMargins(10, 5, 10, 0);


    QPushButton *test = new QPushButton("Press", &window);


    virtual_box->addWidget(test);

    window.setLayout(virtual_box);
    window.show();

    auto sink_qt = std::make_shared<AppSink>();
    logger->registerSink(sink_qt);

    QObject::connect(test, &QPushButton::clicked, []() {
        logger->warn("Warning Meow");
        logger->info("Common Meow");
        logger->error("Dangerous Meow");
    });

    return app.exec();
}

