// Login window header for CRM application
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

#include <openssl/evp.h>
#include <openssl/sha.h>

#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>
#include <iomanip>
#include <sstream>

#include "../database-types/employee.h"
#include "../database-types/leader.h"
#include "../database-types/marketer.h"
#include "../database-types/seller.h"
#include "../database-types/stock_manager.h"
#include "../mainwindow.h"
#include "ui_login.h"

enum class Role { Leader, Manager, Marketer, Seller, Unknown };

namespace Ui {
class loginUi;
}

class login : public QWidget {
    Q_OBJECT

   public:
    explicit login(QMainWindow* parent = nullptr);
    ~login();
    QPushButton* getLoginButton();

   private slots:
    void on_LoginButton_clicked();
    void on_ShowPassword_clicked(bool checked);

   private:
    MainWindow* parent;
    Ui::loginUi* ui;
};
