#ifndef MARKETOLOGIST_H
#define MARKETOLOGIST_H

#include <QWidget>

namespace Ui {
class marketologist;
}

class marketologist : public QWidget
{
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
    Ui::marketologist *ui;
};

#endif // MARKETOLOGIST_H
