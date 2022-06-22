#ifndef SELLER_H
#define SELLER_H

#include <QWidget>

namespace Ui {
class seller;
}

class seller : public QWidget
{
    Q_OBJECT

public:
    explicit seller(QWidget *parent = nullptr);
    ~seller();

signals:
    void logout();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void tableClientUpdate();
    void tableStorageUpdate();
    void tableDealUpdate();

private:
    Ui::seller *ui;
};

#endif // SELLER_H
