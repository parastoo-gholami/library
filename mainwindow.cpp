#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registration.h"
#include "admin.h"
#include "user.h"
#include<QDate>
MainWindow::MainWindow(QList<QString>* groups,QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->info_user = info_user;
    this->info_book = info_book;
    this->groups = groups;
    QDate today(QDate::currentDate());
    this->ui->date->setText(today.toString("dd.MM.yyyy"));
    this->ui->all->setText(QString::number(info_book->count()));
    int count = 0;
    for(int i = 0;i<info_book->count();i++)
    {
        if(info_book->at(i).available == "no")
            count++;
    }
    this->ui->amanat->setText(QString::number(count));
}

MainWindow::~MainWindow()
{
    {

        QFile file("groups.txt");
        if(!file.open(QFile::WriteOnly|QFile::Text))
            return;
        QTextStream qts(&file);
        for(int i = 0;i<groups->count();i++)
        {
            qts<<groups->at(i) + "\n";
        }
    }

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
                    admin* page_a;
                    close();
                    page_a = new admin(i,groups,info_book,info_user);
                    page_a->show();
                }
                else
                {
                    user *page_u;
                    close();
                    page_u = new user(i,groups,info_book,info_user);
                    page_u->show();
                }
            }
        }
        this->ui->textBrowser->setText("username or password is incorrect");
}


void MainWindow::on_register_2_clicked()
{
    close();
    page_r = new registration(groups,info_book,info_user);
    page_r->show();
}



void MainWindow::on_forget_clicked()
{
    close();
    forget_pass *page_fp;
    page_fp = new forget_pass(groups,info_book,info_user);
    page_fp->show();
}

