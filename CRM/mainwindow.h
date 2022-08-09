// MainWindow window header for CRM application
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

#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>

#include "db_pool.h"

namespace Ui {
class MainWindowUi;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void setLeaderInterface();
    void setLoginInterface();
    void setManagerInterface();
    void setMarketerInterface();
    void setSellerInterface();
    db_pool database;
    bool connectDatabase();
    void setDatabase(const std::string& host, const unsigned short int& port,
                     const std::string& user, const std::string& password,
                     const std::string& database);

   private:
    std::string database_ip = "localhost";
    unsigned short int database_port = 5432;
    std::string database_login = "practice";
    std::string database_password = "root";
    std::string database_name = "Practice";
    Ui::MainWindowUi* ui;
    QIcon closeEye = QIcon(QPixmap(":/images/closeEye.png"));
    QIcon openEye = QIcon(QPixmap(":/images/openEye.png"));
    QMessageBox msgBoxEmptyInput;
    QMessageBox msgBoxIncorrectInput;
    std::string get_connection_string();
};
