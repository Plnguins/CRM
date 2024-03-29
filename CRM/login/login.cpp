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

login::login(QMainWindow* parent)
    : parent(dynamic_cast<MainWindow*>(parent)), ui(new Ui::loginUi) {
    ui->setupUi(this);
    if (!this->parent->connectDatabase()) {
        QMessageBox::critical(this, tr("Ошибка"),
                              tr("Невозможно подключиться к БД"));
    }
}

void login::on_ShowPassword_clicked(bool checked) {
    if (checked) {
        ui->Password->setEchoMode(QLineEdit::Normal);
    } else {
        ui->Password->setEchoMode(QLineEdit::Password);
    }
}

void login::on_LoginButton_clicked() {
    if (!this->parent->connectDatabase()) {
        QMessageBox::critical(this, tr("Ошибка"),
                              tr("Невозможно подключиться к БД"));
        return;
    }
    std::string Login, Password;
    Role role = Role::Unknown;
    Login = ui->Login->text().toStdString();
    if (Login.empty() || ui->Password->text().isEmpty()) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Введите логин и пароль"));
        return;
    }
    Password = db_methods::hashPassword(ui->Password->text().toStdString());
    try {
        soci::session sql(*parent->database.get_pool().lock());
        std::string get_employee =
            "SELECT employee.name, employee.surname, employee.password, "
            "leader.id, stock_manager.id, marketer.id, seller.id FROM (((( "
            "employee LEFT OUTER JOIN leader ON leader.employee = employee.id) "
            "LEFT OUTER JOIN stock_manager ON stock_manager.employee = "
            "employee.id) LEFT OUTER JOIN marketer ON marketer.employee = "
            "employee.id) LEFT OUTER JOIN seller ON seller.employee = "
            "employee.id) WHERE login = :login LIMIT 1";
        boost::tuple<boost::optional<std::string>, boost::optional<std::string>,
                     boost::optional<std::string>, boost::optional<int>,
                     boost::optional<int>, boost::optional<int>,
                     boost::optional<int>>
            result;
        sql << get_employee, soci::into(result), soci::use(Login, "login");
        if (!result.get<2>() || result.get<2>().get() != Password) {
            QMessageBox::critical(this, tr("Ошибка"),
                                  tr("Неверный логин или пароль"));
            return;
        }
        if (result.get<3>().is_initialized()) {
            role = Role::Leader;
        } else if (result.get<4>().is_initialized()) {
            role = Role::Manager;
        } else if (result.get<5>().is_initialized()) {
            role = Role::Marketer;
        } else if (result.get<6>().is_initialized()) {
            role = Role::Seller;
        }
        std::string name = result.get<0>().get(),
                    surname = result.get<1>().get();
        switch (role) {
            case Role::Leader:
                parent->setLeaderInterface(name, surname);
                break;
            case Role::Manager:
                parent->setManagerInterface(name, surname);
                break;
            case Role::Marketer:
                parent->setMarketerInterface(name, surname);
                break;
            case Role::Seller:
                parent->setSellerInterface(name, surname);
                break;
            case Role::Unknown:
                QMessageBox::critical(
                    this, tr("Ошибка"),
                    tr("Пользователь не принадлежит ни к одной роли"));
                break;
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Ошибка"),
                              tr("Что-то пошло не так. Ошибка:\n") + e.what());
        // Logging
    }
}
