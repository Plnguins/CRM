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

std::string hashPassword(const std::string &password) {
    // Encrypting and hashing password using PBKDF2 algorithm and hashing using
    // sha512, salt is static, iterations is 4096, result length is 8192
    unsigned char *result = new unsigned char[8192];
    unsigned char salt = 0;
    unsigned int key_length = 8192;
    PKCS5_PBKDF2_HMAC(password.c_str(), password.size(), &salt, 1, 4096,
                      EVP_sha512(), key_length, result);
    unsigned long long *res = reinterpret_cast<unsigned long long *>(result);
    std::stringstream output;
    for (size_t i = 0; i < key_length >> 6; i++) {
        output << std::hex << res[i];
    }
    return output.str();
}

login::login(QMainWindow *parent)
    : parent(dynamic_cast<MainWindow *>(parent)), ui(new Ui::loginUi) {
    ui->setupUi(this);
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

void login::on_ShowPassword_clicked(bool checked) {
    if (checked) {
        ui->Password->setEchoMode(QLineEdit::Normal);
    } else {
        ui->Password->setEchoMode(QLineEdit::Password);
    }
}

void login::on_LoginButton_clicked() {
    std::string Login, Password;
    Role role = Unknown;
    Login = ui->Login->text().toStdString();
    Password = hashPassword(ui->Password->text().toStdString());
    try {
        soci::session sql(*parent->database.get_pool().lock());
        std::string get_employee =
            "SELECT * FROM employee WHERE login = :login AND password = "
            ":password";
        boost::optional<employee> result;
        sql << get_employee, soci::into(result), soci::use(Login, "login"),
            soci::use(Password, "password");
        if (!result.is_initialized()) {
            QMessageBox::critical(this, "Ошибка", "Неверный логин или пароль");
            return;
        }
        boost::optional<leader> result_leader;
        boost::optional<stock_manager> result_stock_manager;
        boost::optional<marketer> result_marketer;
        boost::optional<seller> result_seller;
        std::string check_leader = "SELECT * FROM leader WHERE employee = :id";
        sql << check_leader, soci::into(result_leader),
            soci::use(result.get().id, "id");
        if (result_leader.is_initialized()) {
            role = Leader;
        }
        std::string check_stock_manager =
            "SELECT * FROM stock_manager WHERE employee = :id";
        sql << check_stock_manager, soci::into(result_stock_manager),
            soci::use(result.get().id, "id");
        if (result_stock_manager.is_initialized()) {
            role = Manager;
        }
        std::string check_marketer =
            "SELECT * FROM marketer WHERE employee = :id";
        sql << check_marketer, soci::into(result_marketer),
            soci::use(result.get().id, "id");
        if (result_marketer.is_initialized()) {
            role = Marketer;
        }
        std::string check_seller = "SELECT * FROM seller WHERE employee = :id";
        sql << check_seller, soci::into(result_seller),
            soci::use(result.get().id, "id");
        if (result_seller.is_initialized()) {
            role = Seller;
        }
        switch (role) {
            case Leader:
                parent->setLeaderInterface();
                ui->Login->clear();
                ui->Password->clear();
                break;
            case Manager:
                parent->setManagerInterface();
                ui->Login->clear();
                ui->Password->clear();
                break;
            case Marketer:
                parent->setMarketerInterface();
                ui->Login->clear();
                ui->Password->clear();
                break;
            case Seller:
                parent->setSellerInterface();
                ui->Login->clear();
                ui->Password->clear();
                break;
            case Unknown:
                QMessageBox::critical(
                    this, "Ошибка",
                    "Пользователь не принадлежит ни к одной роли");
                break;
        }
    } catch (const std::exception &e) {
        std::string message = e.what();
        QMessageBox::critical(
            this, "Ошибка",
            ("Что-то пошло не так. Ошибка:\n" + message).c_str());
        // Logging
    }
}
