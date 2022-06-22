#ifndef MANAGER_H
#define MANAGER_H

#include <QWidget>

namespace Ui {
class manager;
}

class manager : public QWidget {
    Q_OBJECT

   public:
    explicit manager(QWidget *parent = nullptr);
    ~manager();

   signals:
    void logout();

   private slots:
    void tableVendorUpdate();
    void tableDealUpdate();
    void tableStorageUpdate();

    void on_pushButton_7_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

   private:
    Ui::manager *ui;
};

#endif  // MANAGER_H
