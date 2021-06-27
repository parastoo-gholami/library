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
    explicit admin(int index,QList<QString>* groups,QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent = nullptr);
    ~admin();

private slots:

    void on_view_clicked();

    void on_add_clicked();

    void on_exit_clicked();

    void on_remove_clicked();

    void on_edit_clicked();

    void on_view_g_clicked();

    void on_ok_clicked();

    void on_num_textChanged(const QString &arg1);

private:
    Ui::admin *ui;
    QList<books>* info_book;
    QList<user_pass>* info_user;
    QList<QString>* groups;
    int index;
};

#endif // ADMIN_H
