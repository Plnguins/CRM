// Manager source code for CRM application
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
#include "managerWidget.h"

managerWidget::managerWidget(QMainWindow* parent)
    : parent(dynamic_cast<MainWindow*>(parent)), ui(new Ui::managerUi) {
    ui->setupUi(this);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);
}

managerWidget::~managerWidget() { delete ui; }

void managerWidget::on_Logout_clicked() {
    ui->Icon->show();
    ui->Title->show();
    ui->Company->show();
    ui->Greeting->show();
    ui->tableWidget->hide();
    ui->RoundedBlue->hide();
    ui->Update->hide();
    ui->Edit->hide();
    ui->Add->hide();
    ui->Delete->hide();
    ui->ProviderLabel->hide();
    ui->Send->hide();
    ui->Help->hide();
    ui->textEdit->hide();
    ui->textEdit->clear();
    parent->setLoginInterface();
}

void managerWidget::on_Provider_clicked() {
    ui->tableWidget->show();
    ui->Update->show();
    ui->Edit->show();
    ui->Add->show();
    ui->Delete->show();
    ui->RoundedBlue->show();
    ui->ProviderLabel->show();
    ui->Icon->hide();
    ui->Title->hide();
    ui->Company->hide();
    ui->Greeting->hide();
    ui->Send->hide();
    ui->Help->hide();
    ui->textEdit->hide();

    ui->ProviderLabel->setText("Поставщики");
    ui->Update->setText("Update");

    // TODO: fill table with db
    // tableVendorUpdate();

    // get from db
    QStringList Labels = {"ID", "Название"};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);
    ui->tableWidget->setRowCount(5);

    // temporary
    QTableWidgetItem* item = new QTableWidgetItem("123");
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 2; j++) {
            QTableWidgetItem* item = new QTableWidgetItem("123");
            ui->tableWidget->setItem(i, j, item);
            ui->tableWidget->item(i, j)->setFlags(Qt::ItemIsEnabled |
                                                  Qt::ItemIsSelectable);
        }
    }
}

void managerWidget::on_Deal_clicked() {
    ui->tableWidget->show();
    ui->Update->show();
    ui->Edit->show();
    ui->Add->show();
    ui->Delete->show();
    ui->RoundedBlue->show();
    ui->ProviderLabel->show();
    ui->Icon->hide();
    ui->Title->hide();
    ui->Company->hide();
    ui->Greeting->hide();
    ui->Send->hide();
    ui->Help->hide();
    ui->textEdit->hide();

    ui->ProviderLabel->setText("Сделки");
    ui->Update->setText("Update");

    // TODO: fill table with db
    // tableDealUpdate();

    // get from db
    QStringList Labels = {"ID",         "Ноутбук", "Цена",
                          "Покупатель", "Статус",  "Дата создания",
                          "Продавец",   "Оценка",  "Последнее обновление"};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    // temporary
    ui->tableWidget->setRowCount(5);
    QTableWidgetItem* item = new QTableWidgetItem("123");
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 9; j++) {
            QTableWidgetItem* item = new QTableWidgetItem("123");
            ui->tableWidget->setItem(i, j, item);
            ui->tableWidget->item(i, j)->setFlags(Qt::ItemIsEnabled |
                                                  Qt::ItemIsSelectable);
        }
    }
}

void managerWidget::on_Stock_clicked() {
    ui->tableWidget->show();
    ui->Update->show();
    ui->Edit->show();
    ui->Add->show();
    ui->Delete->show();
    ui->RoundedBlue->show();
    ui->ProviderLabel->show();
    ui->Icon->hide();
    ui->Title->hide();
    ui->Company->hide();
    ui->Greeting->hide();
    ui->Send->hide();
    ui->Help->hide();
    ui->textEdit->hide();

    ui->ProviderLabel->setText("Склад");
    ui->Update->setText("Update");

    std::vector<boost::tuple<stock, std::string, std::string>> result =
        getStock();

    QStringList Labels = {"ID",         "Ноутбук",  "Цена",
                          "Количество", "Доступно", "Поставщик"};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);
    ui->tableWidget->setRowCount(result.size());
    size_t current_row = 0;
    for (const auto& [stock, laptop_name, provider_name] : result) {
        ui->tableWidget->setItem(
            current_row, 0, new QTableWidgetItem(QString::number(stock.id)));
        ui->tableWidget->setItem(current_row, 1,
                                 new QTableWidgetItem(laptop_name.c_str()));
        ui->tableWidget->setItem(
            current_row, 2, new QTableWidgetItem(QString::number(stock.price)));
        ui->tableWidget->setItem(
            current_row, 3, new QTableWidgetItem(QString::number(stock.count)));
        ui->tableWidget->setItem(
            current_row, 4,
            new QTableWidgetItem(QString::number(stock.available)));
        ui->tableWidget->setItem(current_row, 5,
                                 new QTableWidgetItem(provider_name.c_str()));
        current_row++;
    }
}

std::vector<boost::tuple<stock, std::string, std::string>>
managerWidget::getStock() {
    if (!this->parent->connectDatabase()) {
        QMessageBox::critical(this, "Ошибка", "Невозможно подключиться к БД");
        return std::vector<boost::tuple<stock, std::string, std::string>>();
    }
    std::vector<boost::tuple<stock, std::string, std::string>> result;
    try {
        soci::session sql(*parent->database.get_pool().lock());
        std::string query =
            "SELECT stock.*, laptop.name, provider.name FROM stock JOIN laptop "
            "ON laptop.id=stock.laptop JOIN provider ON "
            "provider.id=stock.source LIMIT 10";
        soci::rowset<boost::tuple<int, int, int, int, int, int, std::string,
                                  std::string>>
            rs = (sql.prepare << query);
        for (auto it = rs.begin(); it != rs.end(); it++) {
            result.push_back({stock(it->get<0>(), it->get<1>(), it->get<2>(),
                                    it->get<3>(), it->get<4>(), it->get<5>()),
                              it->get<6>(), it->get<7>()});
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", e.what());
        return std::vector<boost::tuple<stock, std::string, std::string>>();
    }
    return result;
}
