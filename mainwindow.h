#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "registration.h"
#include "admin.h"
#include "user.h"
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QList<user_pass>* info_user,QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_login_clicked();

    void on_register_2_clicked();

private:
    Ui::MainWindow *ui;
    registration *page_r;
    admin* page_a;
    user *page_u;
    QList<user_pass>*info_user;
};
#endif // MAINWINDOW_H
