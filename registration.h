#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
#include"libraries.h"
namespace Ui {
class registration;
}

class registration : public QDialog
{
    Q_OBJECT

public:
    explicit registration(QList<QString>* groups,QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent = nullptr);
    ~registration();

private slots:
    void on_signup_clicked();

    void on_exit_clicked();

private:
    Ui::registration *ui;
    QList<user_pass>* info_user;
    QList<books>* info_book;
    QList<QString>* groups;
};

#endif // REGISTRATION_H
