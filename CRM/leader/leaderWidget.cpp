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

    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
    ui->pushButton_4->hide();
    ui->pushButton_5->hide();

    ui->pushButton->setText(QString::number(pages[0]));
    ui->pushButton_2->setText(QString::number(pages[1]));
    ui->pushButton_3->setText(QString::number(pages[2]));
    ui->pushButton_4->setText(QString::number(pages[3]));
    ui->pushButton_5->setText(QString::number(pages[4]));
}

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

    curInterface = "Provider";

    if (numberOfPages >= 5) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
        ui->pushButton_5->show();
    } else if (numberOfPages == 4) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
    } else if (numberOfPages == 3) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
    } else if (numberOfPages == 2) {
        ui->pushButton->show();
        ui->pushButton_2->show();
    } else if (numberOfPages == 1) {
        ui->pushButton->show();
    }

    ui->Title->setText("Поставщики");

    ui->tableWidget->clear();
    const QStringList Labels = {"ID", "Название"};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<provider> providers = getProvider(session, 0, 12);
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

    curInterface = "Deal";

    if (numberOfPages >= 5) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
        ui->pushButton_5->show();
    } else if (numberOfPages == 4) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
    } else if (numberOfPages == 3) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
    } else if (numberOfPages == 2) {
        ui->pushButton->show();
        ui->pushButton_2->show();
    } else if (numberOfPages == 1) {
        ui->pushButton->show();
    }

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
            getDeal(session, 0, 12);
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

    curInterface = "Stock";

    if (numberOfPages >= 5) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
        ui->pushButton_5->show();
    } else if (numberOfPages == 4) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
    } else if (numberOfPages == 3) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
    } else if (numberOfPages == 2) {
        ui->pushButton->show();
        ui->pushButton_2->show();
    } else if (numberOfPages == 1) {
        ui->pushButton->show();
    }

    ui->Title->setText("Склад");
    const QStringList Labels = {"ID",         "Ноутбук",  "Цена",
                                "Количество", "Доступно", "Поставщик"};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<boost::tuple<stock, laptop, provider>> result =
            getStock(session, 0, 12);
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

    curInterface = "Ads";

    if (numberOfPages >= 5) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
        ui->pushButton_5->show();
    } else if (numberOfPages == 4) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
    } else if (numberOfPages == 3) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
    } else if (numberOfPages == 2) {
        ui->pushButton->show();
        ui->pushButton_2->show();
    } else if (numberOfPages == 1) {
        ui->pushButton->show();
    }

    ui->Title->setText("Реклама");

    const QStringList Labels = {"ID", "Место", "Бюджет", "Комментарии"};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<advertisement> result = getAdvertisement(session, 0, 12);
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

    curInterface = "Employee";

    if (numberOfPages >= 5) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
        ui->pushButton_5->show();
    } else if (numberOfPages == 4) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
    } else if (numberOfPages == 3) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
    } else if (numberOfPages == 2) {
        ui->pushButton->show();
        ui->pushButton_2->show();
    } else if (numberOfPages == 1) {
        ui->pushButton->show();
    }

    ui->Title->setText("Работники");

    const QStringList Labels = {"ID", "Фамилия", "Имя", "Отчество", "Логин"};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<employee> result = getEmployee(session, 0, 12);

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

void leaderWidget::on_Client_clicked() {
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

    curInterface = "Client";

    if (numberOfPages >= 5) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
        ui->pushButton_5->show();
    } else if (numberOfPages == 4) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
    } else if (numberOfPages == 3) {
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->pushButton_3->show();
    } else if (numberOfPages == 2) {
        ui->pushButton->show();
        ui->pushButton_2->show();
    } else if (numberOfPages == 1) {
        ui->pushButton->show();
    }

    ui->Title->setText("Клиенты");

    const QStringList Labels = {"ID",    "Фамилия", "Имя",   "Отчество",
                                "Город", "Пол",     "email", "Телефон"};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<client> clients = getClient(session, 0, 12);
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

void leaderWidget::changeButtonsText(){
    ui->pushButton->setText(QString::number(pages[0]));
    ui->pushButton_2->setText(QString::number(pages[1]));
    ui->pushButton_3->setText(QString::number(pages[2]));
    ui->pushButton_4->setText(QString::number(pages[3]));
    ui->pushButton_5->setText(QString::number(pages[4]));
}

void leaderWidget::goToPage(int pageNumber) {
    if (curInterface == "Deal") {
        try {
            soci::session session(*parent->database.get_pool().lock());
            std::vector<boost::tuple<deal, laptop, client, employee>> deals =
                getDeal(session, pageNumber - 1, 12);
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
    if (curInterface == "Provider") {
        try {
            soci::session session(*parent->database.get_pool().lock());
            std::vector<provider> providers = getProvider(session, pageNumber - 1, 12);
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
    if (curInterface == "Stock") {
        try {
            soci::session session(*parent->database.get_pool().lock());
            std::vector<boost::tuple<stock, laptop, provider>> result =
                getStock(session, pageNumber - 1, 12);
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
    if (curInterface == "Ads") {
        try {
            soci::session session(*parent->database.get_pool().lock());
            std::vector<advertisement> result = getAdvertisement(session, pageNumber - 1, 12);
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
    if (curInterface == "Employee") {
        try {
            soci::session session(*parent->database.get_pool().lock());
            std::vector<employee> result = getEmployee(session, pageNumber - 1, 12);

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
    if (curInterface == "Client") {
        try {
            soci::session session(*parent->database.get_pool().lock());
            std::vector<client> clients = getClient(session, pageNumber -1, 12);
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
}

void leaderWidget::on_pushButton_clicked()
{
    int cur_left_number = pages[0];
    if (cur_left_number > 2) {
        for (auto &tmp:pages)
            tmp -=2;
        changeButtonsText();
    } else if (cur_left_number > 1) {
        for (auto &tmp:pages)
            tmp -=1;
        changeButtonsText();
    }
    //go to pages[pages[0]]
}

void leaderWidget::on_pushButton_2_clicked()
{
    //go to pages[pages[1]]
}

void leaderWidget::on_pushButton_3_clicked()
{
    //go to pages[pages[2]]
}

void leaderWidget::on_pushButton_4_clicked()
{
    //go to pages[pages[3]]
}

void leaderWidget::on_pushButton_5_clicked()
{
    int cur_right_number = pages[4];
    if (numberOfPages - cur_right_number > 1) {
        for (auto &tmp:pages)
            tmp += 2;
        changeButtonsText();
    } else if (numberOfPages - cur_right_number == 1) {
        for (auto &tmp:pages)
            tmp += 1;
        changeButtonsText();
    }
    //go to pages[pages[4]]
}




