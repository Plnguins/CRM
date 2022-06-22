#include "boss.h"
#include "ui_bosinterface.h"

bosInterface::bosInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bosInterface)
{
    ui->setupUi(this);

    QString path = QDir::currentPath();
    int pos = path.toStdString().rfind('/');
    path.remove(pos+1, path.size()-pos-1);
    ui->pushButton->setIcon(QIcon(path + "files/vendor-white.png"));
    ui->pushButton->setIconSize({30,30});
    ui->pushButton_2->setIcon(QIcon(path + "files/dollar.png"));
    ui->pushButton_2->setIconSize({27, 27});
    ui->pushButton_4->setIcon(QIcon(path + "files/ad-white.png"));
    ui->pushButton_4->setIconSize({27, 27});
    ui->pushButton_5->setIcon(QIcon(path + "files/worker-white.png"));
    ui->pushButton_5->setIconSize({30, 30});
    ui->pushButton_3->setIcon(QIcon(path + "files/sklad-white.png"));
    ui->pushButton_3->setIconSize({30, 30});
    ui->pushButton_6->setIcon(QIcon(path + "files/t-white.png"));
    ui->pushButton_6->setIconSize({28, 28});
    ui->pushButton_7->setIcon(QIcon(path + "files/logout.png"));
    ui->pushButton_7->setIconSize({28,28});

    ui->tableWidget->hide();
    ui->label_9->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
    ui->pushButton_10->hide();
    ui->pushButton_11->hide();
    ui->label_10->hide();
    ui->pushButton_12->hide();
    ui->textBrowser->hide();
    ui->textEdit->hide();

    ui->textEdit->clear();

    QPixmap pixmap("G:\\CRM\\files\\main.ico");
    ui->label_2->setPixmap(pixmap);
}

bosInterface::~bosInterface()
{
    delete ui;
}

void bosInterface::on_pushButton_7_clicked()
{
    emit logout();
    ui->label_2->show();
    ui->label_3->show();
    ui->label_4->show();
    ui->label_5->show();
    ui->tableWidget->hide();
    ui->label_9->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
    ui->pushButton_10->hide();
    ui->pushButton_11->hide();
    ui->label_10->hide();
    ui->pushButton_12->hide();
    ui->textBrowser->hide();
    ui->textEdit->hide();
    ui->textEdit->clear();
}


void bosInterface::on_pushButton_clicked()
{
    ui->tableWidget->show();
    ui->pushButton_8->show();
    ui->pushButton_9->show();
    ui->pushButton_10->show();
    ui->pushButton_11->show();
    ui->label_9->show();
    ui->label_10->show();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->pushButton_12->hide();
    ui->textBrowser->hide();
    ui->textEdit->hide();

    ui->label_10->setText("Поставщики");
    ui->pushButton_8->setText("Update");

    //TODO: fill table with db
    //tableVendorUpdate();


    //get from db
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0, 91);
    ui->tableWidget->setColumnWidth(1, 375);
    QStringList Labels = {"id", "Name"};
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    //temporary
    QTableWidgetItem *item = new QTableWidgetItem("123");
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 2; j++) {
            QTableWidgetItem *item = new QTableWidgetItem("123");
            ui->tableWidget->setItem(i, j, item);
            ui->tableWidget->item(i, j)->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
        }
    }

    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(tableVendorUpdate()));
    //connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(doSmth()));
    //connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(doSmth()));
    //connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(doSmth()));
}

void bosInterface::on_pushButton_2_clicked()
{
    ui->tableWidget->show();
    ui->pushButton_8->show();
    ui->pushButton_9->show();
    ui->pushButton_10->show();
    ui->pushButton_11->show();
    ui->label_9->show();
    ui->label_10->show();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->pushButton_12->hide();
    ui->textBrowser->hide();
    ui->textEdit->hide();

    ui->label_10->setText("Сделки");
    ui->pushButton_8->setText("Update");

    //TODO: fill table with db
    //tableDealUpdate();

    //get from db
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(9);
    QStringList Labels = {"id", "id laptop", "price", "customer", "status", "source", "date", "seller", "mark?"};
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    ui->tableWidget->setColumnWidth(0, 52);
    ui->tableWidget->setColumnWidth(1, 52);
    ui->tableWidget->setColumnWidth(2, 52);
    ui->tableWidget->setColumnWidth(3, 52);
    ui->tableWidget->setColumnWidth(4, 51);
    ui->tableWidget->setColumnWidth(5, 52);
    ui->tableWidget->setColumnWidth(6, 52);
    ui->tableWidget->setColumnWidth(7, 52);
    ui->tableWidget->setColumnWidth(8, 51);

    //temporary
    QTableWidgetItem *item = new QTableWidgetItem("123");
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 9; j++) {
            QTableWidgetItem *item = new QTableWidgetItem("123");
            ui->tableWidget->setItem(i, j, item);
            ui->tableWidget->item(i, j)->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
        }
    }

    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(tableDealUpdate()));
    //connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(doSmth()));
    //connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(doSmth()));
    //connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(doSmth()));
}


void bosInterface::on_pushButton_3_clicked()
{
    ui->tableWidget->show();
    ui->pushButton_8->show();
    ui->pushButton_9->show();
    ui->pushButton_10->show();
    ui->pushButton_11->show();
    ui->label_9->show();
    ui->label_10->show();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->pushButton_12->hide();
    ui->textBrowser->hide();
    ui->textEdit->hide();

    ui->label_10->setText("Склад");
    ui->pushButton_8->setText("Update");

    //TODO: fill table with db
    //tableStorageUpdate();

    //get from db
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(6);
    QStringList Labels = {"id", "id laptop", "price", "number", "available", "source"};
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    ui->tableWidget->setColumnWidth(0, 78);
    ui->tableWidget->setColumnWidth(1, 78);
    ui->tableWidget->setColumnWidth(2, 78);
    ui->tableWidget->setColumnWidth(3, 77);
    ui->tableWidget->setColumnWidth(4, 77);
    ui->tableWidget->setColumnWidth(5, 78);

    //temporary
    QTableWidgetItem *item = new QTableWidgetItem("123");
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 6; j++) {
            QTableWidgetItem *item = new QTableWidgetItem("123");
            ui->tableWidget->setItem(i, j, item);
            ui->tableWidget->item(i, j)->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
        }
    }

    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(tableStorageUpdate()));
    //connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(doSmth()));
    //connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(doSmth()));
    //connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(doSmth()));
}


void bosInterface::on_pushButton_4_clicked()
{
    ui->tableWidget->show();
    ui->pushButton_8->show();
    ui->pushButton_9->show();
    ui->pushButton_10->show();
    ui->pushButton_11->show();
    ui->label_9->show();
    ui->label_10->show();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->pushButton_12->hide();
    ui->textBrowser->hide();
    ui->textEdit->hide();

    ui->label_10->setText("Реклама");
    ui->pushButton_8->setText("Update");

    //TODO: fill table with db
    //tableVendorUpdate();


    //get from db
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0, 91);
    ui->tableWidget->setColumnWidth(1, 375);
    QStringList Labels = {"id", "Place"};
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    //temporary
    QTableWidgetItem *item = new QTableWidgetItem("123");
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 2; j++) {
            QTableWidgetItem *item = new QTableWidgetItem("123");
            ui->tableWidget->setItem(i, j, item);
            ui->tableWidget->item(i, j)->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
        }
    }

    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(tableAdUpdate()));
    //connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(doSmth()));
    //connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(doSmth()));
    //connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(doSmth()));
}


void bosInterface::on_pushButton_5_clicked()
{
    ui->tableWidget->show();
    ui->pushButton_8->show();
    ui->pushButton_9->show();
    ui->pushButton_10->show();
    ui->pushButton_11->show();
    ui->label_9->show();
    ui->label_10->show();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->pushButton_12->hide();
    ui->textBrowser->hide();
    ui->textEdit->hide();

    ui->label_10->setText("Работники");
    ui->pushButton_8->setText("Update");

    //TODO: fill table with db
    //tableVendorUpdate();


    //get from db
    ui->tableWidget->setRowCount(5);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setColumnWidth(0, 90);
    ui->tableWidget->setColumnWidth(1, 136);
    ui->tableWidget->setColumnWidth(2 , 90);
    ui->tableWidget->setColumnWidth(3, 90);
    ui->tableWidget->setColumnWidth(4, 60);
    QStringList Labels = {"id", "FIO", "Login", "Password", "Number"};
    ui->tableWidget->setHorizontalHeaderLabels(Labels);

    //temporary
    QTableWidgetItem *item = new QTableWidgetItem("123");
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 5; j++) {
            QTableWidgetItem *item = new QTableWidgetItem("123");
            ui->tableWidget->setItem(i, j, item);
            ui->tableWidget->item(i, j)->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
        }
    }

    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(tableVendorUpdate()));
    //connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(doSmth()));
    //connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(doSmth()));
    //connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(doSmth()));
}


void bosInterface::on_pushButton_6_clicked()
{
    ui->tableWidget->hide();
    ui->pushButton_8->hide();
    ui->pushButton_9->hide();
    ui->pushButton_10->hide();
    ui->pushButton_11->hide();
    ui->label_9->hide();
    ui->label_10->show();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->pushButton_12->show();
    ui->textBrowser->show();
    ui->textEdit->show();

    ui->label_10->setText("ТехПод");
    ui->pushButton_12->setText("Отправить");
}

//----------table update functions---------------

void bosInterface::tableVendorUpdate()
{
    //
}

void bosInterface::tableDealUpdate()
{
    //
}

void bosInterface::tableStorageUpdate()
{
    //
}

void bosInterface::tableAdUpdate()
{
    //
}

void bosInterface::tableEmployeesUpdate()
{
    //
}

