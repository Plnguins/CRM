// Seller source code for CRM application
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
#include "sellerWidget.h"

sellerWidget::sellerWidget(QMainWindow* parent, std::string name,
                           std::string surname)
    : parent(dynamic_cast<MainWindow*>(parent)), ui(new Ui::sellerUi) {
    ui->setupUi(this);

    ui->Greeting->setText(QString::fromStdString("Добро пожаловать,  " + name +
                                                 " " + surname + "!"));

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);
}

void sellerWidget::on_Client_clicked() {
    ui->tableWidget->show();
    ui->Edit->show();
    ui->Add->show();
    ui->Delete->show();
    ui->RoundedBlue->show();
    ui->Title->show();
    ui->Icon->hide();
    ui->Name->hide();
    ui->Company->hide();
    ui->Greeting->hide();

    ui->Title->setText("Клиенты");

    const QStringList Labels = {"ID",    "Фамилия", "Имя",   "Отчество",
                                "Город", "Пол",     "email", "Телефон"};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<client> clients = getClient(session, 0, 10);
        ui->tableWidget->setRowCount(clients.size());

        size_t current_row = 0;
        for (const auto& client : clients) {
            ui->tableWidget->setItem(
                current_row, 0,
                new QTableWidgetItem(QString::number(client.id)));
            ui->tableWidget->setItem(
                current_row, 1,
                new QTableWidgetItem(QString::fromStdString(client.name)));
            ui->tableWidget->setItem(
                current_row, 2,
                new QTableWidgetItem(QString::fromStdString(client.surname)));
            ui->tableWidget->setItem(
                current_row, 3,
                new QTableWidgetItem(
                    QString::fromStdString(client.patronymic)));
            ui->tableWidget->setItem(
                current_row, 4,
                new QTableWidgetItem(QString::fromStdString(client.city)));
            ui->tableWidget->setItem(
                current_row, 5,
                new QTableWidgetItem(QString::fromStdString(client.sex)));
            ui->tableWidget->setItem(
                current_row, 6,
                new QTableWidgetItem(QString::fromStdString(client.email)));
            ui->tableWidget->setItem(
                current_row, 7,
                new QTableWidgetItem(QString::fromStdString(client.phone)));
            current_row++;
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", e.what());
        return;
    }
}

void sellerWidget::on_Deal_clicked() {
    ui->tableWidget->show();
    ui->Edit->show();
    ui->Add->show();
    ui->Delete->show();
    ui->RoundedBlue->show();
    ui->Title->show();
    ui->Icon->hide();
    ui->Name->hide();
    ui->Company->hide();
    ui->Greeting->hide();

    ui->Title->setText("Сделки");

    ui->tableWidget->clear();
    const QStringList Labels = {
        "ID",         "Ноутбук", "Цена",
        "Покупатель", "Статус",  "Дата создания",
        "Продавец",   "Оценка",  "Последнее обновление"};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<boost::tuple<deal, laptop, client, employee>> deals =
            getDeal(session, 0, 10);
        ui->tableWidget->setRowCount(deals.size());

        size_t current_row = 0;
        for (const auto& [deal, laptop, customer, seller] : deals) {
            ui->tableWidget->setItem(
                current_row, 0, new QTableWidgetItem(QString::number(deal.id)));
            ui->tableWidget->setItem(current_row, 1,
                                     new QTableWidgetItem(laptop.name.c_str()));
            ui->tableWidget->setItem(
                current_row, 2,
                new QTableWidgetItem(QString::number(deal.cost)));
            ui->tableWidget->setItem(
                current_row, 3, new QTableWidgetItem(customer.name.c_str()));
            ui->tableWidget->setItem(current_row, 4,
                                     new QTableWidgetItem(deal.status.c_str()));
            ui->tableWidget->setItem(
                current_row, 5,
                new QTableWidgetItem((std::to_string(deal.created.day()) + "." +
                                      std::to_string(deal.created.month()) +
                                      "." + std::to_string(deal.created.year()))
                                         .c_str()));
            ui->tableWidget->setItem(current_row, 6,
                                     new QTableWidgetItem(seller.name.c_str()));
            ui->tableWidget->setItem(
                current_row, 7,
                new QTableWidgetItem(QString::number(deal.rate)));
            ui->tableWidget->setItem(
                current_row, 8,
                new QTableWidgetItem(
                    (std::to_string(deal.last_update.day()) + "." +
                     std::to_string(deal.last_update.month()) + "." +
                     std::to_string(deal.last_update.year()))
                        .c_str()));
            current_row++;
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", e.what());
        return;
    }
}

void sellerWidget::on_Stock_clicked() {
    ui->tableWidget->show();
    ui->Edit->show();
    ui->Add->show();
    ui->Delete->show();
    ui->RoundedBlue->show();
    ui->Title->show();
    ui->Icon->hide();
    ui->Name->hide();
    ui->Company->hide();
    ui->Greeting->hide();

    ui->Title->setText("Склад");
    const QStringList Labels = {"ID",         "Ноутбук",  "Цена",
                                "Количество", "Доступно", "Поставщик"};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<boost::tuple<stock, laptop, provider>> result =
            getStock(session, 0, 10);
        ui->tableWidget->setRowCount(result.size());
        size_t current_row = 0;
        for (const auto& [stock, laptop, provider] : result) {
            ui->tableWidget->setItem(
                current_row, 0,
                new QTableWidgetItem(QString::number(stock.id)));
            ui->tableWidget->setItem(current_row, 1,
                                     new QTableWidgetItem(laptop.name.c_str()));
            ui->tableWidget->setItem(
                current_row, 2,
                new QTableWidgetItem(QString::number(stock.price)));
            ui->tableWidget->setItem(
                current_row, 3,
                new QTableWidgetItem(QString::number(stock.count)));
            ui->tableWidget->setItem(
                current_row, 4,
                new QTableWidgetItem(QString::number(stock.available)));
            ui->tableWidget->setItem(
                current_row, 5, new QTableWidgetItem(provider.name.c_str()));
            current_row++;
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", e.what());
        return;
    }
}
