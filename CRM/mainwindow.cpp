#include "mainwindow.h"

#include <QFile>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setBossInterface();

    stack.addWidget(loginInterface);
    stack.addWidget(bos);

    setLoginInterface();

    this->setCentralWidget(&stack);

    connect(loginInterface, SIGNAL(bossLogin()), this,
            SLOT(setBossInterface()));
    connect(loginInterface, SIGNAL(managerLogin()), this,
            SLOT(setManagerInterface()));
    connect(loginInterface, SIGNAL(marketologistLogin()), this,
            SLOT(setMarketologistInterface()));
    connect(loginInterface, SIGNAL(sellerLogin()), this,
            SLOT(setSellerInterface()));

    connect(bos, SIGNAL(logout()), this, SLOT(setLoginInterface()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setSellerInterface() {
    stack.setCurrentIndex(4);
    this->setFixedSize({821, 511});
}

void MainWindow::setMarketologistInterface() {
    stack.setCurrentIndex(3);
    this->setFixedSize({821, 511});
}

void MainWindow::setManagerInterface() {
    stack.setCurrentIndex(2);
    this->setFixedSize({821, 511});
}

void MainWindow::setBossInterface() {
    stack.setCurrentIndex(1);
    this->setFixedSize({821, 511});
}

void MainWindow::setLoginInterface() {
    stack.setCurrentIndex(0);
    this->setFixedSize({300, 250});
}
