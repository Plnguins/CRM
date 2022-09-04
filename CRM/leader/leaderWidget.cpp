// Leader source code for CRM application
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
#include "leaderWidget.h"

leaderWidget::leaderWidget(QMainWindow* parent, std::string name,
                           std::string surname)
    : parent(dynamic_cast<MainWindow*>(parent)), ui(new Ui::leaderUi) {
    ui->setupUi(this);

    ui->Greeting->setText(QString::fromStdString("Добро пожаловать,  " + name +
                                                 " " + surname + "!"));

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);
}

leaderWidget::~leaderWidget() { delete ui; }

void leaderWidget::on_Logout_clicked() { parent->setLoginInterface(); }

void leaderWidget::on_Provider_clicked() {
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

    ui->Title->setText("Поставщики");

    ui->tableWidget->clear();
    const QStringList Labels = {"ID", "Название"};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<provider> providers = getProvider(session, 0, 10);
        ui->tableWidget->setRowCount(providers.size());

        size_t current_row = 0;
        for (const auto& current : providers) {
            ui->tableWidget->setItem(
                current_row, 0,
                new QTableWidgetItem(QString::number(current.id)));
            ui->tableWidget->setItem(
                current_row, 1, new QTableWidgetItem(current.name.c_str()));
            current_row++;
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", e.what());
        return;
    }
}

void leaderWidget::on_Deal_clicked() {
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

void leaderWidget::on_Stock_clicked() {
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

void leaderWidget::on_Ads_clicked() {
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

    ui->Title->setText("Реклама");

    const QStringList Labels = {"ID", "Место", "Бюджет", "Комментарии"};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<advertisement> result = getAdvertisement(session, 0, 10);
        ui->tableWidget->setRowCount(result.size());

        size_t current_row = 0;
        for (const auto& ad : result) {
            ui->tableWidget->setItem(
                current_row, 0, new QTableWidgetItem(QString::number(ad.id)));
            ui->tableWidget->setItem(current_row, 1,
                                     new QTableWidgetItem(ad.source.c_str()));
            ui->tableWidget->setItem(
                current_row, 2,
                new QTableWidgetItem(QString::number(ad.budget)));
            ui->tableWidget->setItem(current_row, 3,
                                     new QTableWidgetItem(ad.comments.c_str()));
            current_row++;
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", e.what());
        return;
    }
}

void leaderWidget::on_Employee_clicked() {
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

    ui->Title->setText("Работники");

    const QStringList Labels = {"ID", "Фамилия", "Имя", "Отчество", "Логин"};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<employee> result = getEmployee(session, 0, 10);

        size_t current_row = 0;
        for (const auto& employee : result) {
            ui->tableWidget->setItem(
                current_row, 0,
                new QTableWidgetItem(QString::number(employee.id)));
            ui->tableWidget->setItem(
                current_row, 1, new QTableWidgetItem(employee.surname.c_str()));
            ui->tableWidget->setItem(
                current_row, 2, new QTableWidgetItem(employee.name.c_str()));
            ui->tableWidget->setItem(
                current_row, 3,
                new QTableWidgetItem(employee.patronymic.c_str()));
            ui->tableWidget->setItem(
                current_row, 4, new QTableWidgetItem(employee.login.c_str()));
            current_row++;
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка", e.what());
        return;
    }
}
