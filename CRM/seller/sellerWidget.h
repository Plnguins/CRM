// Seller window header for CRM application
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

#include "../mainwindow.h"
#include "ui_seller.h"

namespace Ui {
class sellerUi;
}

class sellerWidget : public QWidget {
    Q_OBJECT

   public:
    explicit sellerWidget(QMainWindow* parent = nullptr, std::string = "",
                          std::string = "");
    ~sellerWidget();

   signals:
    void logout();

   private slots:
    void on_Client_clicked();

    void on_Deal_clicked();

    void on_Stock_clicked();

    void on_Support_clicked();

    void on_Logout_clicked();

    void tableClientUpdate();
    void tableStorageUpdate();
    void tableDealUpdate();

   private:
    MainWindow* parent;
    Ui::sellerUi* ui;
};
