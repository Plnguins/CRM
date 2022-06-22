// Marketer window header for CRM application
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

#include <QMainWindow>
#include <QWidget>

#include "mainwindow.h"
#include "ui_marketer.h"

namespace Ui {
class marketerUi;
}

class marketer : public QWidget {
    Q_OBJECT

   public:
    explicit marketer(QWidget *parent = nullptr);
    ~marketer();

   private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void tableAdUpdate();

   signals:
    void logout();

   private:
    MainWindow *parent;
    Ui::marketerUi *ui;
};
