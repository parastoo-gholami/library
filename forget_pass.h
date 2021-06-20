#ifndef FORGET_PASS_H
#define FORGET_PASS_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class forget_pass;
}

class forget_pass : public QDialog
{
    Q_OBJECT

public:
    explicit forget_pass(QList<QString>* groups,QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent = nullptr);
    ~forget_pass();

private slots:
    void on_exit_clicked();

    void on_signup_clicked();

private:
    Ui::forget_pass *ui;
    QList<user_pass>* info_user;
    QList<QString>* groups;
    QList<books>* info_book;
};

#endif // FORGET_PASS_H
