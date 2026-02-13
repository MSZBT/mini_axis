#include <QApplication>
#include <QPushButton>
#include <QObject>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <memory>
#include <Qstring>

int main(int argc, char *argv[])
{
    /*инициализация приложения*/
    QApplication app(argc, argv);

    /*рабочее окнго*/
    QWidget window;
    window.setWindowTitle("Logger");
    window.setStyleSheet("QWidget { background-color: #1a1a1a; min-width: 450px; min-height: 300px; }");

    class QLogSpace : public QTextEdit {
    public:
        void appendText(const QString& add_data) {
            QTextEdit::append(add_data);
            QTextEdit::moveCursor(QTextCursor::End);
        }
    };

    auto log_space = std::make_shared<QLogSpace>();
    log_space->setPlainText("Виузальная оболочка для отслеживания логов\n");
    log_space->setReadOnly(true);
    log_space->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    log_space->setAlignment(Qt::AlignBottom);
    log_space->setStyleSheet(
        "QLogSpace {"
        "    background-color: rgb(255, 255, 255);"
        "    color: black;"
        "    text-align: bottom;"
        "    font-size: 22px;"
        /*"   font-family: \"Fira Code\", monospace;"
        "   font-optical-sizing: auto;"
        "   font-weight: 500;"
        "   font-style: normal;"*/
        "}"
    );

    auto scrollArea = std::make_shared<QScrollArea>();
    scrollArea->setWidget(log_space.get());
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { border: none; }");

    QPushButton *test = new QPushButton("Press", &window);


    auto virtual_box = std::make_shared<QVBoxLayout>();
    virtual_box->addWidget(scrollArea.get());
    virtual_box->addWidget(test);
    virtual_box->setContentsMargins(10, 5, 10, 0);
    window.setLayout(virtual_box.get());


    QObject::connect(test, &QPushButton::clicked, [log_space]() {
        log_space->appendText("meow");
    });




    window.show();
    return app.exec();
}