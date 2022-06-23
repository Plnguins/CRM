// Marketer source code for CRM application
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
#include "marketer.h"

marketer::marketer(QWidget *parent)
    : parent(dynamic_cast<MainWindow *>(parent)), ui(new Ui::marketerUi) {
    ui->setupUi(this);

    ui->pushButton_4->setIcon(QIcon(":/images/ad-white.png"));
    ui->pushButton_4->setIconSize({27, 27});
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

marketer::~marketer() { delete ui; }

void marketer::on_pushButton_4_clicked() {
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

    ui->label_10->setText("Реклама");
    ui->pushButton_8->setText("Update");

    // TODO: fill table with db
    // tableVendorUpdate();

    // get from db
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0, 91);
    ui->tableWidget->setColumnWidth(1, 375);
    QStringList Labels = {"id", "Place"};
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    // temporary
    QTableWidgetItem *item = new QTableWidgetItem("123");
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 2; j++) {
            QTableWidgetItem *item = new QTableWidgetItem("123");
            ui->tableWidget->setItem(i, j, item);
            ui->tableWidget->item(i, j)->setFlags(Qt::ItemIsEnabled |
                                                  Qt::ItemIsSelectable);
        }
    }

    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(tableAdUpdate()));
    // connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(doSmth()));
    // connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(doSmth()));
    // connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(doSmth()));
}

void marketer::on_pushButton_6_clicked() {
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

void marketer::on_pushButton_7_clicked() {
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

void marketer::tableAdUpdate() {
    //
}
