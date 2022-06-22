#pragma once

#include <QFile>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>

namespace Ui {
class login;
}

class login : public QWidget {
    Q_OBJECT

   public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    QPushButton *getLoginButton();

   private slots:
    void on_LoginButton_clicked();

   signals:
    void bossLogin();
    void managerLogin();
    void marketologistLogin();
    void sellerLogin();

   private:
    Ui::login *ui;
    QIcon closeEye = QIcon(QPixmap(":/images/closeEye.png"));
    QIcon openEye = QIcon(QPixmap(":/images/openEye.png"));
    QMessageBox msgBoxEmptyInput;
    QMessageBox msgBoxIncorrectInput;
};
