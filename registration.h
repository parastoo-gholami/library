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
    explicit registration(QList<user_pass>* info_user,QWidget *parent = nullptr);
    ~registration();

private slots:
    void on_signup_clicked();

private:
    Ui::registration *ui;
    QList<user_pass>* info_user;
};

#endif // REGISTRATION_H
