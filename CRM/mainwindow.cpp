// MainWindow source code for CRM application
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
#include "mainwindow.h"

#include "leader/leaderWidget.h"
#include "login/login.h"
#include "manager/managerWidget.h"
#include "marketer/marketerWidget.h"
#include "seller/sellerWidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindowUi) {
    QFontDatabase::addApplicationFont(":/Comfortaa.ttf");
    ui->setupUi(this);
    database = db_pool();
    setLoginInterface();
}

void MainWindow::setSellerInterface(std::string name, std::string surname) {
    /*
     * Функция открывает интерфейс продавца
     */
    setCentralWidget(new sellerWidget(this, name, surname));
    setFixedSize({832, 492});
}

void MainWindow::setMarketerInterface(std::string name, std::string surname) {
    /*
     * Функция открывает интерфейс маркетолога
     */
    setCentralWidget(new marketerWidget(this, name, surname));
    setFixedSize({823, 492});
}

void MainWindow::setManagerInterface(std::string name, std::string surname) {
    /*
     * Функция открывает интерфейс менеджера
     */
    setCentralWidget(new managerWidget(this, name, surname));
    setFixedSize({821, 489});
}

void MainWindow::setLeaderInterface(std::string name, std::string surname) {
    /*
     * Функция открывает интерфейс руководителя
     */
    setCentralWidget(new leaderWidget(this, name, surname));
    setFixedSize({821, 492});
}

void MainWindow::setLoginInterface() {
    /*
     * Функция открывает интерфейс авторизации
     */
    setCentralWidget(new login(this));
    setFixedSize({300, 233});
}

bool MainWindow::connectDatabase() {
    /*
     * Функция пытается подключиться к СУБД и возвращает true в случае успеха
     * и false в случае неудачи
     */
    return database.connect(get_connection_string());
}

void MainWindow::setDatabase(const std::string& host,
                             const unsigned short int& port,
                             const std::string& user,
                             const std::string& password,
                             const std::string& database) {
    /*
     * Функция устанавливает параметры подключения к СУБД
     */
    database_ip = host;
    database_port = port;
    database_login = user;
    database_password = password;
    database_name = database;
}

std::string MainWindow::get_connection_string() {
    /*
     * Функция возвращает строку подключения к СУБД
     */
    return "postgresql://host='" + database_ip + "' dbname='" + database_name +
           "' port=" + std::to_string(database_port) + " user='" +
           database_login + "' password='" + database_password + "'";
}
