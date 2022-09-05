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
#include "marketerWidget.h"

marketerWidget::marketerWidget(QWidget* parent, std::string name,
                               std::string surname)
    : parent(dynamic_cast<MainWindow*>(parent)), ui(new Ui::marketerUi) {
    ui->setupUi(this);

    ui->Greeting->setText(QString::fromStdString("Добро пожаловать,  " + name +
                                                 " " + surname + "!"));

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents);
}

void marketerWidget::on_Ads_clicked() {
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
