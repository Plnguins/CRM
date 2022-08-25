// Manager window header for CRM application
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

#include "../database-types/deal.h"
#include "../database-types/provider.h"
#include "../database-types/stock.h"
#include "../mainwindow.h"
#include "ui_manager.h"

namespace Ui {
class managerUi;
}

class managerWidget : public QWidget {
    Q_OBJECT

   public:
    explicit managerWidget(QMainWindow* parent = nullptr, std::string = "",
                           std::string = "");
    ~managerWidget();

   signals:
    void logout();

   private slots:
    std::vector<boost::tuple<stock, std::string, std::string>> getStock();
    std::vector<provider> getProvider();
    std::vector<boost::tuple<deal, std::string, std::string, std::string>>
    getDeal();
    void on_Logout_clicked();
    void on_Provider_clicked();
    void on_Deal_clicked();
    void on_Stock_clicked();

   private:
    MainWindow* parent;
    Ui::managerUi* ui;
};
