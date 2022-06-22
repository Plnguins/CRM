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

#include "boss.h"
#include "login.h"
#include "manager.h"
#include "marketer.h"
#include "seller.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowUi) {
    ui->setupUi(this);

    setLoginInterface();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setSellerInterface() {
    setCentralWidget(new seller(this));
    setFixedSize({821, 511});
}

void MainWindow::setMarketerInterface() {
    setCentralWidget(new marketer(this));
    setFixedSize({821, 511});
}

void MainWindow::setManagerInterface() {
    setCentralWidget(new manager(this));
    setFixedSize({821, 511});
}

void MainWindow::setBossInterface() {
    setCentralWidget(new boss(this));
    setFixedSize({821, 511});
}

void MainWindow::setLoginInterface() {
    setCentralWidget(new login(this));
    setFixedSize({300, 250});
}
