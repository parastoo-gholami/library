#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class admin;
}

class admin : public QDialog
{
    Q_OBJECT

public:
    explicit admin(int index,QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent = nullptr);
    ~admin();

private slots:

    void on_view_clicked();

    void on_add_clicked();

    void on_exit_clicked();

    void on_remove_clicked();

    void on_edit_clicked();

private:
    Ui::admin *ui;
    QList<books>* info_book;
    QList<user_pass>* info_user;
    int index;
};

#endif // ADMIN_H