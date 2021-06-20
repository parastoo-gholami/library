#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "registration.h"
#include "admin.h"
#include "user.h"
#include "forget_pass.h"
#include <QMainWindow>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QList<QString>* groups,QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_login_clicked();

    void on_register_2_clicked();






    void on_forget_clicked();

private:
    Ui::MainWindow *ui;
    registration *page_r;

    QList<user_pass>*info_user;
    QList<books>* info_book;
    QList<QString>* groups;
};
#endif // MAINWINDOW_H
