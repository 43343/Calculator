#include <QApplication>
#include "MainWindow.h"
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/noun_707744-1.ico"));
    MainWindow window;

    window.setWindowTitle("Calculator");
    window.setFixedSize(300, 350);
    window.show();
    return app.exec();
}