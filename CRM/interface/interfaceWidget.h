// Interface header for CRM application
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

#include "../db_methods.h"
#include "../editUI/ui_editClient.h"
#include "../editUI/ui_editAd.h"
#include "../editUI/ui_editDeal.h"
#include "../editUI/ui_editEmployee.h"
#include "../editUI/ui_editProvider.h"
#include "../editUI/ui_editStock.h"
#include "../mainwindow.h"
#include "ui_interface.h"

namespace Ui {
class interfaceUi;
class editAd;
class editDeal;
class editEmployee;
class editProvider;
class editStock;
}  // namespace Ui

class interfaceWidget : public QWidget {
    Q_OBJECT

   public:
    explicit interfaceWidget(QMainWindow* parent = nullptr, std::string = "",
                             std::string = "");
    ~interfaceWidget() { delete ui; }

   private slots:
    void on_Provider_clicked();
    void on_Employee_clicked();
    void on_Stock_clicked();
    void on_Ads_clicked();
    void on_Deal_clicked();
    void on_Client_clicked();

    void on_Add_clicked();
    void on_Edit_clicked();
    void on_Delete_clicked();

    void on_Logout_clicked() { parent->setLoginInterface(); }

    void on_Page_1_clicked();
    void on_Page_2_clicked() { goToPage(pages[1]); }
    void on_Page_3_clicked() { goToPage(pages[2]); }
    void on_Page_4_clicked() { goToPage(pages[3]); }
    void on_Page_5_clicked();

    void on_Catalog_clicked();

protected:
    Ui::interfaceUi* ui;

   private:
    MainWindow* parent;
    int numberOfPages = 0;
    std::vector<short> pages = {1, 2, 3, 4, 5};
    std::vector<QPushButton*> pageButtons;
    int limit = 10;

    void updateProvider(const int& = 0, const int& = 10);
    void updateEmployee(const int& = 0, const int& = 10);
    void updateStock(const int& = 0, const int& = 10);
    void updateAds(const int& = 0, const int& = 10);
    void updateDeal(const int& = 0, const int& = 10);
    void updateClient(const int& = 0, const int& = 10);
    void updateLaptop(const int& = 0, const int& = 10);

    void (interfaceWidget::*updateTable)(const int&, const int&) = nullptr;

    void hideGreeting();
    void updatePageButtons();
    void goToPage(int pageNumber) {
        (this->*updateTable)(pageNumber - 1, limit);
    }
};
