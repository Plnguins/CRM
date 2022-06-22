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

#include <QFile>
#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>

#include "mainwindow.h"
#include "ui_login.h"
namespace Ui {
class loginUi;
}

class login : public QWidget {
    Q_OBJECT

   public:
    explicit login(QMainWindow *parent = nullptr);
    ~login();
    QPushButton *getLoginButton();

   private slots:
    void on_LoginButton_clicked();

   private:
    MainWindow *parent;
    Ui::loginUi *ui;
    QIcon closeEye = QIcon(QPixmap(":/images/closeEye.png"));
    QIcon openEye = QIcon(QPixmap(":/images/openEye.png"));
    QMessageBox msgBoxEmptyInput;
    QMessageBox msgBoxIncorrectInput;
};
