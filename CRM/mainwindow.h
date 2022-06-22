#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QMessageBox>
#include <boss.h>
#include <manager.h>
#include <marketologist.h>
#include <seller.h>
#include <QFontDatabase>
#include <login.h>
#include <QPushButton>
#include <QDebug>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void setBossInterface();
    void setLoginInterface();
    void setManagerInterface();
    void setMarketologistInterface();
    void setSellerInterface();

private:
    Ui::MainWindow *ui;
    QIcon closeEye = QIcon(QPixmap("G:\\CRM\\files\\closeEye.png"));
    QIcon openEye = QIcon(QPixmap("G:\\CRM\\files\\openEye.png"));
    QMessageBox msgBoxEmptyInput;
    QMessageBox msgBoxIncorrectInput;
    bosInterface *bos = new bosInterface();
    login *loginInterface = new login();
    manager *mngr = new manager();
    marketologist *mrktlg = new marketologist();
    seller *slr = new seller();
    QStackedWidget stack;

};
#endif // MAINWINDOW_H
