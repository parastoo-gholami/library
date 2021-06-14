#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registration.h"
#include "admin.h"
#include "user.h"
MainWindow::MainWindow(QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->info_user = info_user;
    this->info_book = info_book;
}

MainWindow::~MainWindow()
{
    {
        QFile file("user_pass.txt");
        if(!file.open(QFile::WriteOnly|QFile::Text))
            return;
        QTextStream qts(&file);
        for(int i = 0;i<info_user->count();i++)
        {
            qts<<info_user->at(i).user + "\n";
            qts<<info_user->at(i).pass + "\n";
            qts<<info_user->at(i).name + "\n";
            qts<<info_user->at(i).email + "\n";
            QString s;
            s = QString::number(info_user->at(i).num);
            qts<<s+"\n";
        }
        file.close();
    }
    {
        QFile file("books.txt");
        if(!file.open(QFile::Text | QFile::WriteOnly))
            return;
        QTextStream qts(&file);
        for(int i = 0;i<info_book->count();i++)
        {
            qts<<info_book->at(i).name + "\n";
            qts<<info_book->at(i).author + "\n";
            qts<<info_book->at(i).publisher + "\n";
            for(int j = 0;j<info_book->at(i).groups.count();j++)
            {
                    qts<<info_book->at(i).groups.at(j)+"\n";
            }
            qts<<info_book->at(i).available + "\n";
            qts<<info_book->at(i).who + "\n";
        }
        file.close();
    }
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
                    admin* page_a;
                    page_a = new admin(i,info_book,info_user);
                    page_a->show();
                }
                else
                {
                    user *page_u;
                    hide();
                    page_u = new user(i,info_book,info_user);
                    page_u->show();
                }
            }
        }
        this->ui->textBrowser->setText("username or password is incorrect");
}


void MainWindow::on_register_2_clicked()
{
    hide();
    page_r = new registration(info_book,info_user);
    page_r->show();
}







