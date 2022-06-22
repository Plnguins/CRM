#include <QApplication>

#include "boss.h"
#include "login.h"
#include "mainwindow.h"

void setBossInterface(MainWindow &w, bosInterface *b) { w.setCentralWidget(b); }

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load(QString("QtLanguage_") + QString("ru_RU"));
    qApp->installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
