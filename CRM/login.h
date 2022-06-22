#pragma once

#include <QFile>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>

#include "mainwindow.h"
#include "ui_login.h"
namespace Ui {
class loginUi;
}

class login : public QWidget {
    Q_OBJECT

   public:
    explicit login(QMainWindow *parent = nullptr);
    ~login();
    QPushButton *getLoginButton();

   private slots:
    void on_LoginButton_clicked();

   private:
    MainWindow *parent;
    Ui::loginUi *ui;
    QIcon closeEye = QIcon(QPixmap(":/images/closeEye.png"));
    QIcon openEye = QIcon(QPixmap(":/images/openEye.png"));
    QMessageBox msgBoxEmptyInput;
    QMessageBox msgBoxIncorrectInput;
};
