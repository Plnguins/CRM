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
#include "seller.h"

seller::seller(QMainWindow *parent)
    : parent(dynamic_cast<MainWindow *>(parent)), ui(new Ui::sellerUi) {
    ui->setupUi(this);

    ui->pushButton->setIcon(QIcon(":/images/client-white.png"));
    ui->pushButton->setIconSize({30, 30});
    ui->pushButton_2->setIcon(QIcon(":/images/dollar.png"));
    ui->pushButton_2->setIconSize({27, 27});
    ui->pushButton_3->setIcon(QIcon(":/images/sklad-white.png"));
    ui->pushButton_3->setIconSize({30, 30});
    ui->pushButton_6->setIcon(QIcon(":/images/t-white.png"));
    ui->pushButton_6->setIconSize({28, 28});
    ui->pushButton_7->setIcon(QIcon(":/images/logout.png"));
    ui->pushButton_7->setIconSize({28, 28});

    ui->tableWidget->hide();
    ui->label_9->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
    ui->pushButton_10->hide();
    ui->pushButton_11->hide();
    ui->label_10->hide();
    ui->pushButton_12->hide();
    ui->textBrowser->hide();
    ui->textEdit->hide();

    ui->textEdit->clear();

    QPixmap pixmap(":/main.ico");
    ui->label_2->setPixmap(pixmap);
}

seller::~seller() { delete ui; }

void seller::on_pushButton_clicked() {
    ui->tableWidget->show();
    ui->pushButton_8->show();
    ui->pushButton_9->show();
    ui->pushButton_10->show();
    ui->pushButton_11->show();
    ui->label_9->show();
    ui->label_10->show();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->pushButton_12->hide();
    ui->textBrowser->hide();
    ui->textEdit->hide();

    ui->label_10->setText("Клиенты");
    ui->pushButton_8->setText("Update");

    // TODO: fill table with db
    // tableVendorUpdate();

    // get from db
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setColumnWidth(0, 65);
    ui->tableWidget->setColumnWidth(1, 96);
    ui->tableWidget->setColumnWidth(2, 65);
    ui->tableWidget->setColumnWidth(3, 65);
    ui->tableWidget->setColumnWidth(4, 45);
    ui->tableWidget->setColumnWidth(5, 65);
    ui->tableWidget->setColumnWidth(6, 65);
    QStringList Labels = {"id", "FIO", "Date", "City", "Sex", "e-mail", "tel"};
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    // temporary
    QTableWidgetItem *item = new QTableWidgetItem("123");
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 7; j++) {
            QTableWidgetItem *item = new QTableWidgetItem("123");
            ui->tableWidget->setItem(i, j, item);
            ui->tableWidget->item(i, j)->setFlags(Qt::ItemIsEnabled |
                                                  Qt::ItemIsSelectable);
        }
    }

    connect(ui->pushButton_8, SIGNAL(clicked()), this,
            SLOT(tableClientUpdate()));
    // connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(doSmth()));
    // connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(doSmth()));
    // connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(doSmth()));
}

void seller::on_pushButton_2_clicked() {
    ui->tableWidget->show();
    ui->pushButton_8->show();
    ui->pushButton_9->show();
    ui->pushButton_10->show();
    ui->pushButton_11->show();
    ui->label_9->show();
    ui->label_10->show();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->pushButton_12->hide();
    ui->textBrowser->hide();
    ui->textEdit->hide();

    ui->label_10->setText("Сделки");
    ui->pushButton_8->setText("Update");

    // TODO: fill table with db
    // tableDealUpdate();

    // get from db
    ui->tableWidget->setRowCount(5);
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
    QTableWidgetItem *item = new QTableWidgetItem("123");
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 9; j++) {
            QTableWidgetItem *item = new QTableWidgetItem("123");
            ui->tableWidget->setItem(i, j, item);
            ui->tableWidget->item(i, j)->setFlags(Qt::ItemIsEnabled |
                                                  Qt::ItemIsSelectable);
        }
    }

    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(tableDealUpdate()));
    // connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(doSmth()));
    // connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(doSmth()));
    // connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(doSmth()));
}

void seller::on_pushButton_3_clicked() {
    ui->tableWidget->show();
    ui->pushButton_8->show();
    ui->pushButton_9->show();
    ui->pushButton_10->show();
    ui->pushButton_11->show();
    ui->label_9->show();
    ui->label_10->show();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->pushButton_12->hide();
    ui->textBrowser->hide();
    ui->textEdit->hide();

    ui->label_10->setText("Склад");
    ui->pushButton_8->setText("Update");

    // TODO: fill table with db
    // tableStorageUpdate();

    // get from db
    ui->tableWidget->setRowCount(5);
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
    QTableWidgetItem *item = new QTableWidgetItem("123");
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 6; j++) {
            QTableWidgetItem *item = new QTableWidgetItem("123");
            ui->tableWidget->setItem(i, j, item);
            ui->tableWidget->item(i, j)->setFlags(Qt::ItemIsEnabled |
                                                  Qt::ItemIsSelectable);
        }
    }

    connect(ui->pushButton_8, SIGNAL(clicked()), this,
            SLOT(tableStorageUpdate()));
    // connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(doSmth()));
    // connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(doSmth()));
    // connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(doSmth()));
}

void seller::on_pushButton_6_clicked() {
    ui->tableWidget->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
    ui->pushButton_10->hide();
    ui->pushButton_11->hide();
    ui->label_9->hide();
    ui->label_10->show();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->pushButton_12->show();
    ui->textBrowser->show();
    ui->textEdit->show();

    ui->label_10->setText("ТехПод");
    ui->pushButton_12->setText("Отправить");
}

void seller::on_pushButton_7_clicked() {
    ui->label_2->show();
    ui->label_3->show();
    ui->label_4->show();
    ui->label_5->show();
    ui->tableWidget->hide();
    ui->label_9->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
    ui->pushButton_10->hide();
    ui->pushButton_11->hide();
    ui->label_10->hide();
    ui->pushButton_12->hide();
    ui->textBrowser->hide();
    ui->textEdit->hide();
    ui->textEdit->clear();
    parent->setLoginInterface();
}

void seller::tableClientUpdate() {
    //
}

void seller::tableStorageUpdate() {}

void seller::tableDealUpdate() {}
