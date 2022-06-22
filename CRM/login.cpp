#include "login.h"

#include "ui_login.h"

login::login(QWidget *parent) : QWidget(parent), ui(new Ui::login) {
    ui->setupUi(this);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->pushButton_2->setIcon(openEye);

    msgBoxEmptyInput.setText("Empty Login or Password");
    msgBoxEmptyInput.setStandardButtons(QMessageBox::Close);
    msgBoxEmptyInput.setIcon(QMessageBox::Warning);
    msgBoxEmptyInput.setWindowTitle("Empty input");

    msgBoxIncorrectInput.setText(
        "Incorrect Login or Password. Please, try again.");
    msgBoxIncorrectInput.setInformativeText(
        "Check if your CapsLock is off and you use correct keyboard layout.");
    msgBoxIncorrectInput.setStandardButtons(QMessageBox::Close);
    msgBoxIncorrectInput.setIcon(QMessageBox::Warning);
    msgBoxIncorrectInput.setWindowTitle("Incorrect data");

    int id = QFontDatabase::addApplicationFont(":/Comfortaa.ttf");
}

login::~login() { delete ui; }

QPushButton *login::getLoginButton() { return ui->pushButton; }

void login::on_pushButton_clicked() {
    QString Login, Password;
    // bossInterface *w = new bossInterface(this);
    bool isInputCorrect = true, isOk = true;
    size_t role;
    Login = ui->lineEdit->text();
    Password = ui->lineEdit_2->text();

    if (Login.isEmpty() || Password.isEmpty()) {
        msgBoxEmptyInput.show();
        isOk = false;
    }

    // TODO: checking Login and Password
    if (!isInputCorrect) {
        msgBoxIncorrectInput.show();
        isOk = false;
    }

    //
    role = Login.toInt();
    //

    if (isOk) {
        if (role == 1) {
            emit bossLogin();
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
        } else if (role == 2) {
            emit managerLogin();
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
        } else if (role == 3) {
            emit marketologistLogin();
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
        } else if (role == 4) {
            emit sellerLogin();
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
        }
    }
}
