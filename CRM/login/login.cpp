// Login source code for CRM application
// Copyright(C) 2022 Plnguins

// This program is free software : you can redistribute it and / or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program.If not, see < https:  // www.gnu.org/licenses/>.
#include "login.h"

login::login(QMainWindow *parent)
    : parent(dynamic_cast<MainWindow *>(parent)), ui(new Ui::loginUi) {
    ui->setupUi(this);
    ui->Login->clear();
    ui->Password->clear();
    ui->Password->setEchoMode(QLineEdit::Password);
    ui->ShowPassword->setIcon(openEye);
    int id = QFontDatabase::addApplicationFont(":/Comfortaa.ttf");
    if (!this->parent->database.connect(
            "postgresql://host='" + this->parent->database_ip + "' dbname='" +
            this->parent->database_name +
            "' port=" + std::to_string(this->parent->database_port) +
            " user='" + this->parent->database_login +
            "' "
            "password='" +
            this->parent->database_password + "'")) {
        QMessageBox::critical(this, "Ошибка", "Невозможно подключиться к БД");
    }
}

login::~login() { delete ui; }

QPushButton *login::getLoginButton() { return ui->LoginButton; }

void login::on_LoginButton_clicked() {
    QString Login, Password;
    // leaderInterface *w = new leaderInterface(this);
    bool isInputCorrect = true, isOk = true;
    size_t role;
    Login = ui->Login->text();
    Password = ui->Password->text();
    if (Login.isEmpty() || Password.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Не все поля заполнены");
        isOk = false;
    }
    // TODO: checking Login and Password
    if (!isInputCorrect) {
        QMessageBox::critical(this, "Ошибка", "Неверный логин или пароль");
        isOk = false;
    }
    role = Login.toInt();
    if (isOk) {
        if (role == 1) {
            parent->setLeaderInterface();
            ui->Login->clear();
            ui->Password->clear();
        } else if (role == 2) {
            parent->setManagerInterface();
            ui->Login->clear();
            ui->Password->clear();
        } else if (role == 3) {
            parent->setMarketerInterface();
            ui->Login->clear();
            ui->Password->clear();
        } else if (role == 4) {
            parent->setSellerInterface();
            ui->Login->clear();
            ui->Password->clear();
        }
    }
}
