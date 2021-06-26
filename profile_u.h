#ifndef PROFILE_U_H
#define PROFILE_U_H

#include <QDialog>
#include "user.h"
namespace Ui {
class profile_u;
}

class profile_u : public QDialog
{
    Q_OBJECT

public:
    explicit profile_u(int index,QList<QString>* groups,QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent = nullptr);
    ~profile_u();

private slots:
    void on_back_clicked();

    void on_exit_clicked();

    void on_exit_3_clicked();

    void on_exit_2_clicked();

private:
    Ui::profile_u *ui;
    int index;
    QList<QString>* groups;
    QList<books>* info_book;
    QList<user_pass>* info_user;
};

#endif // PROFILE_U_H
