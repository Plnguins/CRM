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

managerWidget::managerWidget(QMainWindow* parent, std::string name,
                             std::string surname)
    : parent(dynamic_cast<MainWindow*>(parent)), ui(new Ui::managerUi) {
    ui->setupUi(this);

    ui->Greeting->setText(QString::fromStdString("Добро пожаловать,  " + name +
                                                 " " + surname + "!"));

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

    ui->tableWidget->clear();
    QStringList Labels = {"ID", "Название"};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    std::vector<provider> providers = getProvider();
    ui->tableWidget->setRowCount(providers.size());

    size_t current_row = 0;
    for (const auto& current : providers) {
        ui->tableWidget->setItem(
            current_row, 0, new QTableWidgetItem(QString::number(current.id)));
        ui->tableWidget->setItem(current_row, 1,
                                 new QTableWidgetItem(current.name.c_str()));
        current_row++;
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

    ui->tableWidget->clear();
    QStringList Labels = {"ID",         "Ноутбук", "Цена",
                          "Покупатель", "Статус",  "Дата создания",
                          "Продавец",   "Оценка",  "Последнее обновление"};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    std::vector<boost::tuple<deal, std::string, std::string, std::string>>
        deals = getDeal();
    ui->tableWidget->setRowCount(deals.size());

    size_t current_row = 0;
    for (const auto& [deal, laptop_name, customer_name, seller_name] : deals) {
        ui->tableWidget->setItem(
            current_row, 0, new QTableWidgetItem(QString::number(deal.id)));
        ui->tableWidget->setItem(current_row, 1,
                                 new QTableWidgetItem(laptop_name.c_str()));
        ui->tableWidget->setItem(
            current_row, 2, new QTableWidgetItem(QString::number(deal.cost)));
        ui->tableWidget->setItem(current_row, 3,
                                 new QTableWidgetItem(customer_name.c_str()));
        ui->tableWidget->setItem(current_row, 4,
                                 new QTableWidgetItem(deal.status.c_str()));
        ui->tableWidget->setItem(
            current_row, 5,
            new QTableWidgetItem((std::to_string(deal.created.day()) + "." +
                                  std::to_string(deal.created.month()) + "." +
                                  std::to_string(deal.created.year()))
                                     .c_str()));
        ui->tableWidget->setItem(current_row, 6,
                                 new QTableWidgetItem(seller_name.c_str()));
        ui->tableWidget->setItem(
            current_row, 7, new QTableWidgetItem(QString::number(deal.rate)));
        ui->tableWidget->setItem(
            current_row, 8,
            new QTableWidgetItem((std::to_string(deal.last_update.day()) + "." +
                                  std::to_string(deal.last_update.month()) +
                                  "." + std::to_string(deal.last_update.year()))
                                     .c_str()));
        current_row++;
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

    ui->tableWidget->clear();
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
            "ON laptop.id = stock.laptop JOIN provider ON "
            "provider.id = stock.source LIMIT 10";
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

std::vector<provider> managerWidget::getProvider() {
    if (!this->parent->connectDatabase()) {
        QMessageBox::critical(this, "Ошибка", "Невозможно подключиться к БД");
        return std::vector<provider>();
    }
    std::vector<provider> result;
    try {
        soci::session sql(*parent->database.get_pool().lock());
        std::string query = "SELECT * FROM provider";
        soci::rowset<provider> rs = (sql.prepare << query);
        for (auto it = rs.begin(); it != rs.end(); it++) {
            auto current = *it;
            result.push_back(current);
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", e.what());
        return std::vector<provider>();
    }
    return result;
}

std::vector<boost::tuple<deal, std::string, std::string, std::string>>
managerWidget::getDeal() {
    if (!this->parent->connectDatabase()) {
        QMessageBox::critical(this, "Ошибка", "Невозможно подключиться к БД");
        return std::vector<
            boost::tuple<deal, std::string, std::string, std::string>>();
    }
    std::vector<boost::tuple<deal, std::string, std::string, std::string>>
        result;
    try {
        soci::session sql(*parent->database.get_pool().lock());
        std::string query =
            "SELECT deal.*, laptop.name, client.surname, employee.surname FROM "
            "deal JOIN laptop ON laptop.id = deal.laptop JOIN client ON "
            "client.id = deal.client JOIN employee ON employee.id = "
            "deal.seller";
        soci::rowset<soci::row> rs = (sql.prepare << query);
        for (auto it = rs.begin(); it != rs.end(); it++) {
            const auto& row = *it;
            result.push_back(
                {deal(row.get<int>(0), row.get<int>(1), row.get<int>(2),
                      row.get<int>(3), row.get<std::string>(4),
                      row.get<boost::gregorian::date>(5), row.get<int>(6),
                      row.get<int>(7, 0), row.get<boost::gregorian::date>(8)),
                 row.get<std::string>(9), row.get<std::string>(10),
                 row.get<std::string>(11)});
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", e.what());
        return std::vector<
            boost::tuple<deal, std::string, std::string, std::string>>();
    }
    return result;
}
