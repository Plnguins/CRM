// Interface source code for CRM application
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
#include "interfaceWidget.h"

interfaceWidget::interfaceWidget(QMainWindow* parent, std::string name,
                                 std::string surname)
    : parent(dynamic_cast<MainWindow*>(parent)), ui(new Ui::interfaceUi) {
    ui->setupUi(this);

    pageButtons = std::vector<QPushButton*>(
        {ui->Page_1, ui->Page_2, ui->Page_3, ui->Page_4, ui->Page_5});

    ui->Greeting->setText(tr("Добро пожаловать, ") +
                          QString::fromStdString(name + " " + surname + "!"));

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);

    updatePageButtons();
}

void interfaceWidget::on_Provider_clicked() {
    /*
     * Функция отображает поставщиков
     */
    hideGreeting();
    updateTable = &interfaceWidget::updateProvider;
    editElement = &interfaceWidget::editProvider;
    deleteElement = &interfaceWidget::deleteProvider;
    addElement = &interfaceWidget::addProvider;
    goToPage(1);
    updatePageButtons();
}

void interfaceWidget::on_Deal_clicked() {
    /*
     * Функция отображает сделки
     */
    hideGreeting();
    updateTable = &interfaceWidget::updateDeal;
    editElement = &interfaceWidget::editDeal;
    deleteElement = &interfaceWidget::deleteDeal;
    addElement = &interfaceWidget::addDeal;
    goToPage(1);
    updatePageButtons();
}

void interfaceWidget::on_Stock_clicked() {
    /*
     * Функция отображает склад
     */
    hideGreeting();
    updateTable = &interfaceWidget::updateStock;
    editElement = &interfaceWidget::editStock;
    deleteElement = &interfaceWidget::deleteStock;
    addElement = &interfaceWidget::addStock;
    goToPage(1);
    updatePageButtons();
}

void interfaceWidget::on_Ads_clicked() {
    /*
     * Функция отображает рекламные компании
     */
    hideGreeting();
    updateTable = &interfaceWidget::updateAds;
    editElement = &interfaceWidget::editAd;
    deleteElement = &interfaceWidget::deleteAd;
    addElement = &interfaceWidget::addAd;
    goToPage(1);
    updatePageButtons();
}

void interfaceWidget::on_Employee_clicked() {
    /*
     * Функция отображает сотрудников
     */
    hideGreeting();
    updateTable = &interfaceWidget::updateEmployee;
    editElement = &interfaceWidget::editEmployee;
    deleteElement = &interfaceWidget::deleteEmployee;
    addElement = &interfaceWidget::addEmployee;
    goToPage(1);
    updatePageButtons();
}

void interfaceWidget::on_Client_clicked() {
    /*
     * Функция отображает клиентов
     */
    hideGreeting();
    updateTable = &interfaceWidget::updateClient;
    editElement = &interfaceWidget::editClient;
    deleteElement = &interfaceWidget::deleteClient;
    addElement = &interfaceWidget::addClient;
    goToPage(1);
    updatePageButtons();
}

void interfaceWidget::on_Laptop_clicked() {
    /*
     * Функция отображает ноутбуки
     */
    hideGreeting();
    updateTable = &interfaceWidget::updateLaptop;
    editElement = &interfaceWidget::editLaptop;
    deleteElement = &interfaceWidget::deleteLaptop;
    addElement = &interfaceWidget::addLaptop;
    goToPage(1);
    updatePageButtons();
}

void interfaceWidget::on_Add_clicked() {
    try {
        soci::session session(*parent->database.get_pool().lock());
        (this->*addElement)(session);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Ошибка"), e.what());
    }
}

void interfaceWidget::on_Edit_clicked() {
    QItemSelectionModel* select = ui->tableWidget->selectionModel();
    if (!select->hasSelection()) {
        QMessageBox::warning(this, "Внимание", "Выберете один элемент");
        return;
    }
    auto elements = select->selectedIndexes();
    int column = elements[0].column();
    std::vector<int> ids;
    for (const auto& element : elements) {
        if (element.column() != column) {
            continue;
        }
        ids.push_back(ui->tableWidget->item(element.row(), 0)->text().toInt());
    }
    if (ids.size() > 1) {
        QMessageBox::warning(this, "Внимание", "Выберете один элемент");
        return;
    }
    try {
        soci::session session(*parent->database.get_pool().lock());
        if (editElement) {
            (this->*editElement)(session, ids[0]);
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Ошибка"), e.what());
    }
}

void interfaceWidget::on_Delete_clicked() {
    QItemSelectionModel* select = ui->tableWidget->selectionModel();
    if (!select->hasSelection()) {
        QMessageBox::warning(this, "Внимание", "Выберете элемент/элементы");
        return;
    }
    auto elements = select->selectedIndexes();
    int column = elements[0].column();
    std::vector<int> ids;
    for (const auto& element : elements) {
        if (element.column() != column) {
            continue;
        }
        ids.push_back(ui->tableWidget->item(element.row(), 0)->text().toInt());
    }
    try {
        soci::session session(*parent->database.get_pool().lock());
        if (deleteElement) {
            (this->*deleteElement)(session, ids);
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Ошибка"), e.what());
    }
}

void interfaceWidget::hideGreeting() {
    /*
     * Функция скрывает приветствие и показывает таблицу
     */
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
}

void interfaceWidget::updateProvider(const int& page, const int& limit) {
    /*
     * Функция получает данные о поставщиках и отображает в таблице
     */
    ui->Title->setText(tr("Поставщики"));

    ui->tableWidget->clear();
    const QStringList Labels = {tr("ID"), tr("Название")};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<provider> providers =
            db_methods::getProvider(session, page, limit);
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
        numberOfPages = ceil(static_cast<double>(db_methods::row_count) /
                             static_cast<double>(limit));
    } catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Ошибка"), e.what());
        return;
    }
}

void interfaceWidget::updateDeal(const int& page, const int& limit) {
    /*
     * Функция получает данные о сделках и отображает в таблице
     */
    ui->Title->setText(tr("Сделки"));

    ui->tableWidget->clear();
    const QStringList Labels = {
        tr("ID"),         tr("Ноутбук"), tr("Цена"),
        tr("Покупатель"), tr("Статус"),  tr("Дата создания"),
        tr("Продавец"),   tr("Оценка"),  tr("Последнее обновление")};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<boost::tuple<deal, laptop, client, employee>> deals =
            db_methods::getDeal(session, page, limit);
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
        numberOfPages = ceil(static_cast<double>(db_methods::row_count) /
                             static_cast<double>(limit));
    } catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Ошибка"), e.what());
        return;
    }
}

void interfaceWidget::updateStock(const int& page, const int& limit) {
    /*
     * Функция получает данные о складе и отображает в таблице
     */
    ui->Title->setText(tr("Склад"));

    ui->tableWidget->clear();
    const QStringList Labels = {tr("ID"),       tr("Ноутбук"),
                                tr("Цена"),     tr("Количество"),
                                tr("Доступно"), tr("Поставщик")};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<boost::tuple<stock, laptop, provider>> result =
            db_methods::getStock(session, page, limit);
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
        numberOfPages = ceil(static_cast<double>(db_methods::row_count) /
                             static_cast<double>(limit));
    } catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Ошибка"), e.what());
        return;
    }
}

void interfaceWidget::updateAds(const int& page, const int& limit) {
    ui->Title->setText(tr("Реклама"));

    ui->tableWidget->clear();
    const QStringList Labels = {tr("ID"), tr("Платформа"), tr("Бюджет"),
                                tr("Комментарии")};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<advertisement> result =
            db_methods::getAdvertisement(session, page, limit);
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
        numberOfPages = ceil(static_cast<double>(db_methods::row_count) /
                             static_cast<double>(limit));
    } catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Ошибка"), e.what());
        return;
    }
}

void interfaceWidget::updateEmployee(const int& page, const int& limit) {
    /*
     * Функция получает данные о сотрудниках и отображает в таблице
     */
    ui->Title->setText(tr("Работники"));

    ui->tableWidget->clear();
    const QStringList Labels = {tr("ID"), tr("Фамилия"), tr("Имя"),
                                tr("Отчество"), tr("Логин")};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<employee> result =
            db_methods::getEmployee(session, page, limit);
        ui->tableWidget->setRowCount(result.size());

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
        numberOfPages = ceil(static_cast<double>(db_methods::row_count) /
                             static_cast<double>(limit));
    } catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Ошибка"), e.what());
        return;
    }
}

void interfaceWidget::updateClient(const int& page, const int& limit) {
    /*
     * Функция получает данные о клиентах и отображает в таблице
     */
    ui->Title->setText(tr("Клиенты"));

    ui->tableWidget->clear();
    const QStringList Labels = {tr("ID"),       tr("Фамилия"), tr("Имя"),
                                tr("Отчество"), tr("Город"),   tr("Пол"),
                                tr("email"),    tr("Телефон")};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<client> clients =
            db_methods::getClient(session, page, limit);
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
        numberOfPages = ceil(static_cast<double>(db_methods::row_count) /
                             static_cast<double>(limit));
    } catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Ошибка"), e.what());
        return;
    }
}

void interfaceWidget::updateLaptop(const int& page, const int& limit) {
    /*
     * Функция получает данные о клиентах и отображает в таблице
     */
    ui->Title->setText(tr("Ноутбуки"));

    ui->tableWidget->clear();
    const QStringList Labels = {tr("ID"),  tr("Название"),  tr("Прибыль"),
                                tr("Тип"), tr("Процессор"), tr("ГПУ"),
                                tr("ОЗУ"), tr("ПЗУ"),       tr("Цвет")};
    ui->tableWidget->setColumnCount(Labels.size());
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    try {
        soci::session session(*parent->database.get_pool().lock());
        std::vector<laptop> laptops =
            db_methods::getLaptop(session, page, limit);
        ui->tableWidget->setRowCount(laptops.size());

        size_t current_row = 0;
        for (const auto& laptop : laptops) {
            ui->tableWidget->setItem(
                current_row, 0,
                new QTableWidgetItem(QString::number(laptop.id)));
            ui->tableWidget->setItem(
                current_row, 1,
                new QTableWidgetItem(QString::fromStdString(laptop.name)));
            ui->tableWidget->setItem(
                current_row, 2,
                new QTableWidgetItem(QString::number(laptop.income)));
            ui->tableWidget->setItem(
                current_row, 3,
                new QTableWidgetItem(QString::fromStdString(laptop.type)));
            ui->tableWidget->setItem(
                current_row, 4,
                new QTableWidgetItem(QString::fromStdString(laptop.cpu)));
            ui->tableWidget->setItem(
                current_row, 5,
                new QTableWidgetItem(QString::fromStdString(laptop.gpu)));
            ui->tableWidget->setItem(
                current_row, 6,
                new QTableWidgetItem(QString::number(laptop.ram)));
            ui->tableWidget->setItem(
                current_row, 7,
                new QTableWidgetItem(QString::number(laptop.rom)));
            ui->tableWidget->setItem(
                current_row, 8,
                new QTableWidgetItem(QString::fromStdString(laptop.color)));

            current_row++;
        }
        numberOfPages = ceil(static_cast<double>(db_methods::row_count) /
                             static_cast<double>(limit));
    } catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Ошибка"), e.what());
        return;
    }
}

void interfaceWidget::editProvider(soci::session& session, const int& id) {
    provider current = db_methods::getProvider(session, id);
    QDialog* dialog = new QDialog(this);
    Ui::editProvider edit_provider;
    edit_provider.setupUi(dialog);
    connect(edit_provider.Apply, &QPushButton::clicked, dialog,
            &QDialog::accept);
    edit_provider.NameEnter->setText(current.name.c_str());
    connect(edit_provider.Apply, &QPushButton::clicked, dialog, [=]() {
        std::string name = edit_provider.NameEnter->text().toStdString();
        provider updated(current.id, name);
        if (name.empty()) {
            QMessageBox::warning(this, tr("Ошибка"), tr("Заполните все поля!"));
            return;
        }
        try {
            soci::session session(*parent->database.get_pool().lock());
            db_methods::updateProvider(session, updated);
        } catch (const std::exception& e) {
            QMessageBox::warning(this, tr("Ошибка"),
                                 tr("Ошибка при изменении поставщика: ") +
                                     QString::fromStdString(e.what()));
            return;
        }
        dialog->accept();
        goToPage(1);
    });
    dialog->exec();
}

void interfaceWidget::editEmployee(soci::session& session, const int& id) {}

void interfaceWidget::editStock(soci::session& session, const int& id) {}

void interfaceWidget::editAd(soci::session& session, const int& id) {
    advertisement current = db_methods::getAd(session, id);
    QDialog* dialog = new QDialog(this);
    Ui::editAd edit_ad;
    edit_ad.setupUi(dialog);
    connect(edit_ad.Apply, &QPushButton::clicked, dialog, &QDialog::accept);
    edit_ad.PlatformEnter->setText(current.source.c_str());
    edit_ad.BudgetEnter->setText(QString::number(current.budget));
    edit_ad.CommentsEnter->setText(current.comments.c_str());
    connect(edit_ad.Apply, &QPushButton::clicked, dialog, [=]() {
        std::string source = edit_ad.PlatformEnter->text().toStdString(),
                    comments = edit_ad.CommentsEnter->text().toStdString();
        int budget = edit_ad.BudgetEnter->text().toInt();
        advertisement updated(current.id, source, budget, comments);
        if (source.empty() || comments.empty() || budget == 0) {
            QMessageBox::warning(this, tr("Ошибка"), tr("Заполните все поля!"));
            return;
        }
        try {
            soci::session session(*parent->database.get_pool().lock());
            db_methods::updateAd(session, updated);
        } catch (const std::exception& e) {
            QMessageBox::warning(this, tr("Ошибка"),
                                 tr("Ошибка при изменении рекламы: ") +
                                     QString::fromStdString(e.what()));
            return;
        }
        dialog->accept();
        goToPage(1);
    });
    dialog->exec();
}

void interfaceWidget::editDeal(soci::session& session, const int& id) {}

void interfaceWidget::editClient(soci::session& session, const int& id) {
    client current = db_methods::getClient(session, id);
    QDialog* dialog = new QDialog(this);
    Ui::editClient edit_client;
    edit_client.setupUi(dialog);
    connect(edit_client.Apply, &QPushButton::clicked, dialog, &QDialog::accept);
    edit_client.SurnameEnter->setText(current.surname.c_str());
    edit_client.NameEnter->setText(current.name.c_str());
    edit_client.PatronymicEnter->setText(current.patronymic.c_str());
    edit_client.PhoneNumberEnter->setText(current.phone.c_str());
    edit_client.CityEnter->setText(current.city.c_str());
    edit_client.SexEnter->setText(current.sex.c_str());
    edit_client.EmailEnter->setText(current.email.c_str());
    connect(edit_client.Apply, &QPushButton::clicked, dialog, [=]() {
        std::string surname = edit_client.SurnameEnter->text().toStdString(),
                    name = edit_client.NameEnter->text().toStdString(),
                    patronymic =
                        edit_client.PatronymicEnter->text().toStdString(),
                    phone = edit_client.PhoneNumberEnter->text().toStdString(),
                    email = edit_client.EmailEnter->text().toStdString(),
                    sex = edit_client.SexEnter->text().toStdString(),
                    city = edit_client.CityEnter->text().toStdString();
        client updated(current.id, surname, name, patronymic, phone, email, sex,
                       city);
        if (surname.empty() || name.empty() || patronymic.empty() ||
            phone.empty() || email.empty() || sex.empty() || city.empty()) {
            QMessageBox::warning(this, tr("Ошибка"), tr("Заполните все поля!"));
            return;
        }
        try {
            soci::session session(*parent->database.get_pool().lock());
            db_methods::updateClient(session, updated);
        } catch (const std::exception& e) {
            QMessageBox::warning(this, tr("Ошибка"),
                                 tr("Ошибка при изменении клиента: ") +
                                     QString::fromStdString(e.what()));
            return;
        }
        dialog->accept();
        goToPage(1);
    });
    dialog->exec();
}

void interfaceWidget::editLaptop(soci::session& session, const int& id) {
    laptop current = db_methods::getLaptop(session, id);
    QDialog* dialog = new QDialog(this);
    Ui::editLaptop edit_laptop;
    edit_laptop.setupUi(dialog);
    edit_laptop.NameEnter->setText(current.name.c_str());
    edit_laptop.IncomeEnter->setText(QString::number(current.income));
    edit_laptop.TypeEnter->setText(current.type.c_str());
    edit_laptop.CPUEnter->setText(current.cpu.c_str());
    edit_laptop.GPUEnter->setText(current.gpu.c_str());
    edit_laptop.RAMEnter->setText(QString::number(current.ram));
    edit_laptop.ROMEnter->setText(QString::number(current.rom));
    edit_laptop.ColorEnter->setText(current.color.c_str());
    soci::session* session_ptr = std::addressof(session);
    connect(edit_laptop.Apply, &QPushButton::clicked, dialog, [=]() {
        std::string name = edit_laptop.NameEnter->text().toStdString(),
                    type = edit_laptop.TypeEnter->text().toStdString(),
                    cpu = edit_laptop.CPUEnter->text().toStdString(),
                    gpu = edit_laptop.GPUEnter->text().toStdString(),
                    color = edit_laptop.ColorEnter->text().toStdString();
        int income = edit_laptop.IncomeEnter->text().toInt(),
            ram = edit_laptop.RAMEnter->text().toInt(),
            rom = edit_laptop.ROMEnter->text().toInt();
        if (name.empty() || type.empty() || cpu.empty() || gpu.empty() ||
            color.empty() || income == 0 || ram == 0 || rom == 0) {
            QMessageBox::warning(this, tr("Ошибка"), tr("Заполните все поля!"));
            return;
        }
        laptop new_laptop(current.id, name, income, type, cpu, gpu, ram, rom,
                          color);
        try {
            db_methods::updateLaptop(*session_ptr, new_laptop);
        } catch (const std::exception& e) {
            QMessageBox::warning(this, tr("Ошибка"),
                                 tr("Ошибка при добавлении клиента: ") +
                                     QString::fromStdString(e.what()));
            return;
        }
        dialog->accept();
        goToPage(1);
    });
    dialog->exec();
}

void interfaceWidget::deleteProvider(soci::session& session,
                                     const std::vector<int>& ids) {
    db_methods::deleteProvider(session, ids);
    goToPage(1);
    QMessageBox::information(this, tr("Успех"), tr("Успешное удаление"));
}

void interfaceWidget::deleteEmployee(soci::session& session,
                                     const std::vector<int>& ids) {
    db_methods::deleteEmployee(session, ids);
    goToPage(1);
    QMessageBox::information(this, tr("Успех"), tr("Успешное удаление"));
}

void interfaceWidget::deleteStock(soci::session& session,
                                  const std::vector<int>& ids) {
    db_methods::deleteStock(session, ids);
    goToPage(1);
    QMessageBox::information(this, tr("Успех"), tr("Успешное удаление"));
}

void interfaceWidget::deleteAd(soci::session& session,
                               const std::vector<int>& ids) {
    db_methods::deleteAd(session, ids);
    goToPage(1);
    QMessageBox::information(this, tr("Успех"), tr("Успешное удаление"));
}

void interfaceWidget::deleteDeal(soci::session& session,
                                 const std::vector<int>& ids) {
    db_methods::deleteDeal(session, ids);
    goToPage(1);
    QMessageBox::information(this, tr("Успех"), tr("Успешное удаление"));
}

void interfaceWidget::deleteClient(soci::session& session,
                                   const std::vector<int>& ids) {
    db_methods::deleteClient(session, ids);
    goToPage(1);
    QMessageBox::information(this, tr("Успех"), tr("Успешное удаление"));
}

void interfaceWidget::deleteLaptop(soci::session& session,
                                   const std::vector<int>& ids) {
    db_methods::deleteLaptop(session, ids);
    goToPage(1);
    QMessageBox::information(this, tr("Успех"), tr("Успешное удаление"));
}

void interfaceWidget::addProvider(soci::session& session) {
    QDialog* dialog = new QDialog(this);
    Ui::editProvider edit_provider;
    edit_provider.setupUi(dialog);
    soci::session* session_ptr = std::addressof(session);
    connect(edit_provider.Apply, &QPushButton::clicked, dialog, [=]() {
        std::string name = edit_provider.NameEnter->text().toStdString();
        if (name.empty()) {
            QMessageBox::warning(this, tr("Ошибка"), tr("Заполните все поля!"));
            return;
        }
        provider new_provider(0, name);
        try {
            db_methods::newProvider(*session_ptr, new_provider);
        } catch (const std::exception& e) {
            QMessageBox::warning(this, tr("Ошибка"),
                                 tr("Ошибка при добавлении поставщика: ") +
                                     QString::fromStdString(e.what()));
            return;
        }
        dialog->accept();
        goToPage(1);
    });
    dialog->exec();
}

void interfaceWidget::addEmployee(soci::session& session) {}

void interfaceWidget::addStock(soci::session& session) {}

void interfaceWidget::addAd(soci::session& session) {
    QDialog* dialog = new QDialog(this);
    Ui::editAd edit_ad;
    edit_ad.setupUi(dialog);
    soci::session* session_ptr = std::addressof(session);
    connect(edit_ad.Apply, &QPushButton::clicked, dialog, [=]() {
        std::string source = edit_ad.PlatformEnter->text().toStdString(),
                    comments = edit_ad.CommentsEnter->text().toStdString();
        int budget = edit_ad.BudgetEnter->text().toInt();
        if (source.empty() || comments.empty() || budget == 0) {
            QMessageBox::warning(this, tr("Ошибка"), tr("Заполните все поля!"));
            return;
        }
        advertisement new_ad(0, source, budget, comments);
        try {
            db_methods::newAd(*session_ptr, new_ad);
        } catch (const std::exception& e) {
            QMessageBox::warning(this, tr("Ошибка"),
                                 tr("Ошибка при добавлении поставщика: ") +
                                     QString::fromStdString(e.what()));
            return;
        }
        dialog->accept();
        goToPage(1);
    });
    dialog->exec();
}

void interfaceWidget::addDeal(soci::session& session) {}

void interfaceWidget::addClient(soci::session& session) {
    QDialog* dialog = new QDialog(this);
    Ui::editClient edit_client;
    edit_client.setupUi(dialog);
    soci::session* session_ptr = std::addressof(session);
    connect(edit_client.Apply, &QPushButton::clicked, dialog, [=]() {
        std::string surname = edit_client.SurnameEnter->text().toStdString(),
                    name = edit_client.NameEnter->text().toStdString(),
                    patronymic =
                        edit_client.PatronymicEnter->text().toStdString(),
                    phone = edit_client.PhoneNumberEnter->text().toStdString(),
                    email = edit_client.EmailEnter->text().toStdString(),
                    sex = edit_client.SexEnter->text().toStdString(),
                    city = edit_client.CityEnter->text().toStdString();
        if (surname.empty() || name.empty() || patronymic.empty() ||
            phone.empty() || email.empty() || sex.empty() || city.empty()) {
            QMessageBox::warning(this, tr("Ошибка"), tr("Заполните все поля!"));
            return;
        }
        client new_client(0, surname, name, patronymic, email, phone, sex,
                          city);
        try {
            db_methods::newClient(*session_ptr, new_client);
        } catch (const std::exception& e) {
            QMessageBox::warning(this, tr("Ошибка"),
                                 tr("Ошибка при добавлении клиента: ") +
                                     QString::fromStdString(e.what()));
            return;
        }
        dialog->accept();
        goToPage(1);
    });
    dialog->exec();
}

void interfaceWidget::addLaptop(soci::session& session) {
    QDialog* dialog = new QDialog(this);
    Ui::editLaptop edit_laptop;
    edit_laptop.setupUi(dialog);
    soci::session* session_ptr = std::addressof(session);
    connect(edit_laptop.Apply, &QPushButton::clicked, dialog, [=]() {
        std::string name = edit_laptop.NameEnter->text().toStdString(),
                    type = edit_laptop.TypeEnter->text().toStdString(),
                    cpu = edit_laptop.CPUEnter->text().toStdString(),
                    gpu = edit_laptop.GPUEnter->text().toStdString(),
                    color = edit_laptop.ColorEnter->text().toStdString();
        int income = edit_laptop.IncomeEnter->text().toInt(),
            ram = edit_laptop.RAMEnter->text().toInt(),
            rom = edit_laptop.ROMEnter->text().toInt();
        if (name.empty() || type.empty() || cpu.empty() || gpu.empty() ||
            color.empty() || income == 0 || ram == 0 || rom == 0) {
            QMessageBox::warning(this, tr("Ошибка"), tr("Заполните все поля!"));
            return;
        }
        laptop new_laptop(0, name, income, type, cpu, gpu, ram, rom, color);
        try {
            db_methods::newLaptop(*session_ptr, new_laptop);
        } catch (const std::exception& e) {
            QMessageBox::warning(this, tr("Ошибка"),
                                 tr("Ошибка при добавлении клиента: ") +
                                     QString::fromStdString(e.what()));
            return;
        }
        dialog->accept();
        goToPage(1);
    });
    dialog->exec();
}

void interfaceWidget::updatePageButtons() {
    /*
     * Функция обновляет текст кнопок, отображает нужные
     */
    for (size_t current = 0; current < pageButtons.size(); current++) {
        pageButtons[current]->setText(QString::number(pages[current]));
    }
    for (const auto& button : pageButtons) {
        button->hide();
    }
    for (size_t current = 0; current < std::min(numberOfPages, 5); current++) {
        pageButtons[current]->show();
    }
}

void interfaceWidget::on_Page_1_clicked() {
    int cur_left_number = pages[0];
    if (cur_left_number > 2) {
        for (auto& tmp : pages) tmp -= 2;
        updatePageButtons();
    } else if (cur_left_number > 1) {
        for (auto& tmp : pages) tmp -= 1;
        updatePageButtons();
    }
    goToPage(pages[0]);
}

void interfaceWidget::on_Page_5_clicked() {
    int cur_right_number = pages[4];
    if (numberOfPages - cur_right_number > 1) {
        for (auto& tmp : pages) tmp += 2;
        updatePageButtons();
    } else if (numberOfPages - cur_right_number == 1) {
        for (auto& tmp : pages) tmp += 1;
        updatePageButtons();
    }
    goToPage(pages[4]);
}
