#ifndef USER_H
#define USER_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class user;
}

class user : public QDialog
{
    Q_OBJECT

public:
    explicit user(int index,QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent = nullptr);
    ~user();

private slots:
    void on_exit_clicked();

    void on_view_clicked();


    void on_borrow_clicked();

    void on_returnbook_clicked();

    void on_profile_clicked();

private:
    Ui::user *ui;
    QList<user_pass>*info_user;
    QList<books>* info_book;
    int index;
};

#endif // USER_H
