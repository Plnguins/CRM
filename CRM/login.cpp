#include "login.h"

login::login(QMainWindow *parent)
    : parent(dynamic_cast<MainWindow *>(parent)), ui(new Ui::loginUi) {
    ui->setupUi(this);
    ui->Login->clear();
    ui->Password->clear();
    ui->Password->setEchoMode(QLineEdit::Password);
    ui->ShowPassword->setIcon(openEye);
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

QPushButton *login::getLoginButton() { return ui->LoginButton; }

void login::on_LoginButton_clicked() {
    QString Login, Password;
    // bossInterface *w = new bossInterface(this);
    bool isInputCorrect = true, isOk = true;
    size_t role;
    Login = ui->Login->text();
    Password = ui->Password->text();
    if (Login.isEmpty() || Password.isEmpty()) {
        msgBoxEmptyInput.show();
        isOk = false;
    }
    // TODO: checking Login and Password
    if (!isInputCorrect) {
        msgBoxIncorrectInput.show();
        isOk = false;
    }
    role = Login.toInt();
    if (isOk) {
        if (role == 1) {
            parent->setBossInterface();
            ui->Login->clear();
            ui->Password->clear();
        } else if (role == 2) {
            parent->setManagerInterface();
            ui->Login->clear();
            ui->Password->clear();
        } else if (role == 3) {
            parent->setMarketologistInterface();
            ui->Login->clear();
            ui->Password->clear();
        } else if (role == 4) {
            parent->setSellerInterface();
            ui->Login->clear();
            ui->Password->clear();
        }
    }
}
