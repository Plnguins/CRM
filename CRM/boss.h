#ifndef BOSS_H
#define BOSS_H

#include <QWidget>
#include <QTranslator>
#include <QDir>
#include <iostream>
#include <QtDebug>

namespace Ui {
class bosInterface;
}

class bosInterface : public QWidget
{
    Q_OBJECT

public:
    explicit bosInterface(QWidget *parent = nullptr);
    ~bosInterface();

signals:
    void logout();

private slots:
    void on_pushButton_7_clicked();
    void on_pushButton_clicked();
    void tableVendorUpdate();
    void tableDealUpdate();
    void tableStorageUpdate();
    void tableAdUpdate();
    void tableEmployeesUpdate();


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::bosInterface *ui;
    QTranslator translator;
};

#endif // BOSS_H
