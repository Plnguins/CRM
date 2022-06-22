#include "mainwindow.h"

#include <QFile>

#include "boss.h"
#include "login.h"
#include "manager.h"
#include "marketologist.h"
#include "seller.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowUi) {
    ui->setupUi(this);

    setLoginInterface();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setSellerInterface() {
    setCentralWidget(new seller(this));
    setFixedSize({821, 511});
}

void MainWindow::setMarketologistInterface() {
    setCentralWidget(new marketologist(this));
    setFixedSize({821, 511});
}

void MainWindow::setManagerInterface() {
    setCentralWidget(new manager(this));
    setFixedSize({821, 511});
}

void MainWindow::setBossInterface() {
    setCentralWidget(new boss(this));
    setFixedSize({821, 511});
}

void MainWindow::setLoginInterface() {
    setCentralWidget(new login(this));
    setFixedSize({300, 250});
}
