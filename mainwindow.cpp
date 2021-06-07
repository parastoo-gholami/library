#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registration.h"
#include "admin.h"
#include "user.h"
MainWindow::MainWindow(QList<user_pass>* info_user,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->info_user = info_user;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_login_clicked()
{
    if(this->ui->username->text() == nullptr)
    {
        this->ui->textBrowser->setText("enter your username");
        return;
    }
    if(this->ui->password->text() == nullptr)
    {
        this->ui->textBrowser->setText("enter your password");
        return;
    }
    user_pass tmp;
        tmp.user = this->ui->username->text();
        tmp.pass = this->ui->password->text();
        for(int i=0;i<(*info_user).count();++i)
        {
            if(info_user->at(i).user == tmp.user)
            if(info_user->at(i).pass == tmp.pass)
            {
                if(this->ui->username->text() == "Admin")
                {
                    hide();
                    page_a = new admin();
                    page_a->show();
                }
                else
                {
                    hide();
                    page_u = new user();
                    page_u->show();
                }
            }
        }
        this->ui->textBrowser->setText("username or password is incorrect");
}


void MainWindow::on_register_2_clicked()
{
    hide();
    page_r = new registration(info_user);
    page_r->show();
}

