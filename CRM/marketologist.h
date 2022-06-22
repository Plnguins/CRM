#pragma once

#include <QMainWindow>
#include <QWidget>

#include "mainwindow.h"
#include "ui_marketologist.h"

namespace Ui {
class marketologistUi;
}

class marketologist : public QWidget {
    Q_OBJECT

   public:
    explicit marketologist(QWidget *parent = nullptr);
    ~marketologist();

   private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void tableAdUpdate();

   signals:
    void logout();

   private:
    MainWindow *parent;
    Ui::marketologistUi *ui;
};
