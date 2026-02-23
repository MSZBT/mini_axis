#include "axis/qt_app.h"


#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>

#include <memory>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    QLoggerSpace* log_space = new QLoggerSpace();

    QList<QLoggerSpace*> logs_manager;
    logs_manager.push_back(log_space);

    auto logger = std::make_shared<LocalLogger>();

    std::shared_ptr<QtAppSink> sink_qt = std::make_shared<QtAppSink>(logs_manager);
    sink_qt->register_ui();

    logger->registerSink(sink_qt);

    QWidget window;
    window.setWindowTitle("Logger");
    window.setStyleSheet("QWidget { background-color: #1a1a1a; min-width: 450px; min-height: 300px; }");


    auto virtual_box = new QVBoxLayout();
    virtual_box->addWidget(log_space);
    virtual_box->setContentsMargins(10, 5, 10, 0);


    QPushButton *test = new QPushButton("Press", &window);


    virtual_box->addWidget(test);

    window.setLayout(virtual_box);
    window.show();


    /**/
    QObject::connect(test, &QPushButton::clicked, [logger]() {
        logger->warn("Warning Meow");
    });




    return app.exec();
}
