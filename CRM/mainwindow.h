#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QStackedWidget>
#include <iostream>

#include "boss.h"
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private slots:
    void setBossInterface();
    void setLoginInterface();
    void setManagerInterface();
    void setMarketologistInterface();
    void setSellerInterface();

   private:
    Ui::MainWindow *ui;
    QIcon closeEye = QIcon(QPixmap(":/images/closeEye.png"));
    QIcon openEye = QIcon(QPixmap(":/images/openEye.png"));
    QMessageBox msgBoxEmptyInput;
    QMessageBox msgBoxIncorrectInput;
    bosInterface *bos = new bosInterface();
    login *loginInterface = new login();
    QStackedWidget stack;
};
#endif  // MAINWINDOW_H
