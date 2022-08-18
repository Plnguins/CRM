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
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0, 91);
    ui->tableWidget->setColumnWidth(1, 375);
    QStringList Labels = {"id", "Name"};
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

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

    connect(ui->Update, SIGNAL(clicked()), this, SLOT(tableVendorUpdate()));
    // connect(ui->Edit, SIGNAL(clicked()), this, SLOT(doSmth()));
    // connect(ui->Add, SIGNAL(clicked()), this, SLOT(doSmth()));
    // connect(ui->Delete, SIGNAL(clicked()), this, SLOT(doSmth()));
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
    ui->tableWidget->setColumnCount(9);
    QStringList Labels = {"id",     "id laptop", "price",  "customer", "status",
                          "source", "date",      "seller", "mark?"};
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    ui->tableWidget->setColumnWidth(0, 52);
    ui->tableWidget->setColumnWidth(1, 52);
    ui->tableWidget->setColumnWidth(2, 52);
    ui->tableWidget->setColumnWidth(3, 52);
    ui->tableWidget->setColumnWidth(4, 51);
    ui->tableWidget->setColumnWidth(5, 52);
    ui->tableWidget->setColumnWidth(6, 52);
    ui->tableWidget->setColumnWidth(7, 52);
    ui->tableWidget->setColumnWidth(8, 51);

    // temporary
    QTableWidgetItem* item = new QTableWidgetItem("123");
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 9; j++) {
            QTableWidgetItem* item = new QTableWidgetItem("123");
            ui->tableWidget->setItem(i, j, item);
            ui->tableWidget->item(i, j)->setFlags(Qt::ItemIsEnabled |
                                                  Qt::ItemIsSelectable);
        }
    }

    connect(ui->Update, SIGNAL(clicked()), this, SLOT(tableDealUpdate()));
    // connect(ui->Edit, SIGNAL(clicked()), this, SLOT(doSmth()));
    // connect(ui->Add, SIGNAL(clicked()), this, SLOT(doSmth()));
    // connect(ui->Delete, SIGNAL(clicked()), this, SLOT(doSmth()));
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

    // TODO: fill table with db
    // tableStorageUpdate();

    // get from db
    ui->tableWidget->setColumnCount(6);
    QStringList Labels = {"id",     "id laptop", "price",
                          "number", "available", "source"};
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    ui->tableWidget->setColumnWidth(0, 78);
    ui->tableWidget->setColumnWidth(1, 78);
    ui->tableWidget->setColumnWidth(2, 78);
    ui->tableWidget->setColumnWidth(3, 77);
    ui->tableWidget->setColumnWidth(4, 77);
    ui->tableWidget->setColumnWidth(5, 78);

    // temporary
    QTableWidgetItem* item = new QTableWidgetItem("123");
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 6; j++) {
            QTableWidgetItem* item = new QTableWidgetItem("123");
            ui->tableWidget->setItem(i, j, item);
            ui->tableWidget->item(i, j)->setFlags(Qt::ItemIsEnabled |
                                                  Qt::ItemIsSelectable);
        }
    }

    connect(ui->Update, SIGNAL(clicked()), this, SLOT(tableStorageUpdate()));
    // connect(ui->Edit, SIGNAL(clicked()), this, SLOT(doSmth()));
    // connect(ui->Add, SIGNAL(clicked()), this, SLOT(doSmth()));
    // connect(ui->Delete, SIGNAL(clicked()), this, SLOT(doSmth()));
}

void managerWidget::on_Support_clicked() {
    ui->tableWidget->hide();
    ui->Update->hide();
    ui->Edit->hide();
    ui->Add->hide();
    ui->Delete->hide();
    ui->RoundedBlue->hide();
    ui->ProviderLabel->show();
    ui->Icon->hide();
    ui->Title->hide();
    ui->Company->hide();
    ui->Greeting->hide();
    ui->Send->show();
    ui->Help->show();
    ui->textEdit->show();

    ui->ProviderLabel->setText("ТехПод");
    ui->Send->setText("Отправить");
}

void managerWidget::tableVendorUpdate() {
    //
}

void managerWidget::tableDealUpdate() {
    //
}

void managerWidget::tableStorageUpdate() {
    //
}
