#include <QApplication>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QTextEdit>
#include <memory>
#include <Qstring>
#include <format>

/*Не используется в готовой версии*/
#include <QPushButton>
#include <QObject>

int main(int argc, char *argv[])
{
    /*инициализация приложения*/
    QApplication app(argc, argv);

    /*рабочее окнго*/
    QWidget window;
    window.setWindowTitle("Logger");
    window.setStyleSheet("QWidget { background-color: #1a1a1a; min-width: 450px; min-height: 300px; }");

    /*класс для поля выввода логов*/
    class QLoggerSpace : public QTextEdit {
    public:
        QLoggerSpace() {
            setPlainText("Виузальная оболочка для отслеживания логов\n");
            setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            setAlignment(Qt::AlignBottom);
            setReadOnly(true);

            setStyleSheet(
                "QTextEdit {"
                "    color: white;"
                "    font-size: 28px;"
                "}"
            );
        }

        /*метод добавления строки*/
        /*параметры флагов 0  - простой вывод 1  - предупреждение -1 - ошибка*/
        void appendText(const QString& add_data, int flag) {
            auto fit_string = std::make_shared<std::string>("white");

            switch (flag) {
                case 1:
                    *fit_string.get() = "yellow";
                    break;
                case -1:
                    *fit_string.get() = "red";
                    break;
            }

            append(QString::fromStdString(std::format("<font color=\"{}\">{}</font>", *fit_string.get(), add_data.toStdString())));
            moveCursor(QTextCursor::End);
        }
    };

    /*Объект по поля логов*/
    auto log_space = std::make_shared<QLoggerSpace>();

    auto scrollArea = std::make_shared<QScrollArea>();
    scrollArea->setWidget(log_space.get());
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { border: none; }");



    /*разметка для окна*/
    auto virtual_box = std::make_shared<QVBoxLayout>();

    virtual_box->addWidget(scrollArea.get());
    virtual_box->setContentsMargins(10, 5, 10, 0);


    /*Для теста отображения ошибок*/
    //QPushButton *test = new QPushButton("Press", &window);
    //QObject::connect(test, &QPushButton::clicked, [log_space]() { log_space->appendText("moew", 1);});
    //virtual_box->addWidget(test);

    window.setLayout(virtual_box.get());
    window.show();
    return app.exec();
}