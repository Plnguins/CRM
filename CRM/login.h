#ifndef LOGIN_H
#define LOGIN_H

#include <QFile>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>
#include <iostream>

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
    void on_pushButton_clicked();

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

#endif  // LOGIN_H
