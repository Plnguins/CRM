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

#include "../mainwindow.h"
#include "ui_db_settings.h"

namespace Ui {
class db_settingsUi;
}

class db_settings : public QWidget {
    Q_OBJECT

   public:
    explicit db_settings(QMainWindow* parent = nullptr);
    ~db_settings() { delete ui; }

   private slots:
    void on_ApplyButton_clicked();

   private:
    Ui::db_settingsUi* ui;
    MainWindow* parent;
};
