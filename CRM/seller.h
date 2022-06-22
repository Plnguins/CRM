#pragma once

#include <QMainWindow>
#include <QWidget>

#include "mainwindow.h"
#include "ui_seller.h"

namespace Ui {
class sellerUi;
}

class seller : public QWidget {
    Q_OBJECT

   public:
    explicit seller(QMainWindow *parent = nullptr);
    ~seller();

   signals:
    void logout();

   private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void tableClientUpdate();
    void tableStorageUpdate();
    void tableDealUpdate();

   private:
    MainWindow *parent;
    Ui::sellerUi *ui;
};
