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

    ui->Ads->setIcon(QIcon(":/images/ad-white.png"));
    ui->Ads->setIconSize({27, 27});
    ui->Support->setIcon(QIcon(":/images/t-white.png"));
    ui->Support->setIconSize({28, 28});
    ui->Logout->setIcon(QIcon(":/images/logout.png"));
    ui->Logout->setIconSize({28, 28});

    ui->tableWidget->hide();
    ui->RoundedBlue->hide();
    ui->Update->hide();
    ui->Edit->hide();
    ui->Add->hide();
    ui->Delete->hide();
    ui->Title->hide();
    ui->Send->hide();
    ui->Help->hide();
    ui->textEdit->hide();

    ui->textEdit->clear();

    QPixmap pixmap(":/main.ico");
    ui->Icon->setPixmap(pixmap);
}

marketer::~marketer() { delete ui; }

void marketer::on_Ads_clicked() {
    ui->tableWidget->show();
    ui->Update->show();
    ui->Edit->show();
    ui->Add->show();
    ui->Delete->show();
    ui->RoundedBlue->show();
    ui->Title->show();
    ui->Icon->hide();
    ui->Name->hide();
    ui->Company->hide();
    ui->Greeting->hide();
    ui->Send->hide();
    ui->Help->hide();
    ui->textEdit->hide();

    ui->Title->setText("Реклама");
    ui->Update->setText("Update");

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

    connect(ui->Update, SIGNAL(clicked()), this, SLOT(tableAdUpdate()));
    // connect(ui->Edit, SIGNAL(clicked()), this, SLOT(doSmth()));
    // connect(ui->Add, SIGNAL(clicked()), this, SLOT(doSmth()));
    // connect(ui->Delete, SIGNAL(clicked()), this, SLOT(doSmth()));
}

void marketer::on_Support_clicked() {
    ui->tableWidget->hide();
    ui->Update->hide();
    ui->Edit->hide();
    ui->Add->hide();
    ui->Delete->hide();
    ui->RoundedBlue->hide();
    ui->Title->show();
    ui->Icon->hide();
    ui->Name->hide();
    ui->Company->hide();
    ui->Greeting->hide();
    ui->Send->show();
    ui->Help->show();
    ui->textEdit->show();

    ui->Title->setText("ТехПод");
    ui->Send->setText("Отправить");
}

void marketer::on_Logout_clicked() {
    ui->Icon->show();
    ui->Name->show();
    ui->Company->show();
    ui->Greeting->show();
    ui->tableWidget->hide();
    ui->RoundedBlue->hide();
    ui->Update->hide();
    ui->Edit->hide();
    ui->Add->hide();
    ui->Delete->hide();
    ui->Title->hide();
    ui->Send->hide();
    ui->Help->hide();
    ui->textEdit->hide();
    ui->textEdit->clear();
    parent->setLoginInterface();
}

void marketer::tableAdUpdate() {
    //
}
