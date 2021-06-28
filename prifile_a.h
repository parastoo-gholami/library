#ifndef PRIFILE_A_H
#define PRIFILE_A_H

#include <QDialog>
#include "user.h"
namespace Ui {
class prifile_a;
}

class prifile_a : public QDialog
{
    Q_OBJECT

public:
    explicit prifile_a(int index,QList<QString>* groups,QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent = nullptr);
    ~prifile_a();

private slots:
    void on_back_clicked();

    void on_exit_3_clicked();

    void on_exit_5_clicked();

    void on_exit_2_clicked();



    void on_exit_clicked();

private:
    Ui::prifile_a *ui;
    int index;
    QList<QString>* groups;
    QList<books>* info_book;
    QList<user_pass>* info_user;
};

#endif // PRIFILE_A_H
