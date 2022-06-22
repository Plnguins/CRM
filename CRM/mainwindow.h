#pragma once

#include <QFontDatabase>
#include <QMainWindow>
#include <QMessageBox>

#include "ui_mainwindow.h"

namespace Ui {
class MainWindowUi;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setBossInterface();
    void setLoginInterface();
    void setManagerInterface();
    void setMarketologistInterface();
    void setSellerInterface();

   private:
    Ui::MainWindowUi *ui;
    QIcon closeEye = QIcon(QPixmap(":/images/closeEye.png"));
    QIcon openEye = QIcon(QPixmap(":/images/openEye.png"));
    QMessageBox msgBoxEmptyInput;
    QMessageBox msgBoxIncorrectInput;
};
