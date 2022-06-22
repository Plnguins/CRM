#pragma once

#include <QMainWindow>
#include <QWidget>

#include "mainwindow.h"
#include "ui_manager.h"
namespace Ui {
class managerUi;
}

class manager : public QWidget {
    Q_OBJECT

   public:
    explicit manager(QMainWindow *parent = nullptr);
    ~manager();

   signals:
    void logout();

   private slots:
    void tableVendorUpdate();
    void tableDealUpdate();
    void tableStorageUpdate();

    void on_Logout_clicked();

    void on_Provider_clicked();

    void on_Deal_clicked();

    void on_Stock_clicked();

    void on_Support_clicked();

   private:
    MainWindow *parent;
    Ui::managerUi *ui;
};
