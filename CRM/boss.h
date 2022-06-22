#pragma once

#include <QDir>
#include <QTranslator>
#include <QWidget>
#include <QtDebug>
#include <iostream>

namespace Ui {
class bosInterface;
}

class bosInterface : public QWidget {
    Q_OBJECT

   public:
    explicit bosInterface(QWidget *parent = nullptr);
    ~bosInterface();

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
    Ui::bosInterface *ui;
    QTranslator translator;
};
