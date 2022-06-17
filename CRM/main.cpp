// Main source code for CRM application
// Copyright(C) 2022 VadVergasov as part of Plnguins

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
#include <soci/postgresql/soci-postgresql.h>
#include <soci/soci.h>

#include <QMainWindow>
#include <QtWidgets/QApplication>

#include "Login/ui_Login.h"

int main(int argc, char* argv[]) {
    Ui::Login ui;
    QApplication a(argc, argv);
    QMainWindow windows;
    QWidget login;
    ui.setupUi(&login);
    windows.setCentralWidget(&login);
    windows.setWindowTitle(login.windowTitle());
    windows.show();
    return a.exec();
}