// vLogin window header for CRM application
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
#pragma once

#include "db_settings.h"

db_settings::db_settings(QMainWindow* parent)
    : parent(dynamic_cast<MainWindow*>(parent)), ui(new Ui::db_settingsUi) {
    ui->setupUi(this);

    ui->DataBaseIPEnter->setText(this->parent->getDataBaseIP().c_str());
    ui->DataBasePortEnter->setText(
        QString::number(this->parent->getDataBasePort()));
    ui->DataBaseLoginEnter->setText(this->parent->getDataBaseLogin().c_str());
    ui->DataBasePasswordEnter->setText(
        this->parent->getDataBasePassword().c_str());
    ui->DataBaseNameEnter->setText(this->parent->getDataBaseName().c_str());
}

void db_settings::on_ApplyButton_clicked() {
    std::string database_ip = ui->DataBaseIPEnter->text().toStdString();
    unsigned short int database_port = ui->DataBasePortEnter->text().toUShort();
    std::string database_login = ui->DataBaseLoginEnter->text().toStdString();
    std::string database_password =
        ui->DataBasePasswordEnter->text().toStdString();
    std::string database_name = ui->DataBaseNameEnter->text().toStdString();

    parent->setDatabase(database_ip, database_port, database_login,
                        database_password, database_name);

    if (!this->parent->connectDatabase()) {
        QMessageBox::critical(this, "Ошибка", "Невозможно подключиться к БД");
    } else {
        parent->setLoginInterface();
    }
}

void db_settings::on_ShowPassword_clicked(bool checked) {
    if (checked) {
        ui->DataBasePasswordEnter->setEchoMode(QLineEdit::Normal);
    } else {
        ui->DataBasePasswordEnter->setEchoMode(QLineEdit::Password);
    }
}
