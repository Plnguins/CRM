#pragma once

#include <QTranslator>
#include <QWidget>
#include <QtDebug>

#include "mainwindow.h"
#include "ui_boss.h"

namespace Ui {
class bossUi;
}

class boss : public QWidget {
    Q_OBJECT

   public:
    explicit boss(QMainWindow *parent = nullptr);
    ~boss();

   signals:
    void logout();

   private slots:
    void on_Provider_clicked();
    void tableVendorUpdate();
    void tableDealUpdate();
    void tableStorageUpdate();
    void tableAdUpdate();
    void tableEmployeesUpdate();

    void on_Employee_clicked();

    void on_Stock_clicked();

    void on_Ads_clicked();

    void on_Logout_clicked();

    void on_Deal_clicked();

    void on_Support_clicked();

   private:
    MainWindow *parent;
    Ui::bossUi *ui;
    QTranslator translator;
};
