#include "forget_pass.h"
#include "ui_forget_pass.h"
#include "mainwindow.h"
forget_pass::forget_pass(QList<QString>* groups,QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forget_pass)
{
    ui->setupUi(this);
    this->info_user = info_user;
    this->info_book = info_book;
    this->groups = groups;
}

forget_pass::~forget_pass()
{
    delete ui;
}

void forget_pass::on_exit_clicked()
{
    if(this->ui->username->text() == nullptr)
        this->ui->textBrowser->setText("enter your username.");
    if(this->ui->name->text() == nullptr)
        this->ui->textBrowser->setText("enter you name.");
    if(this->ui->email->text() == nullptr)
        this->ui->textBrowser->setText("enter you email.");
    for(int i = 0;i<info_user->count() ; i++)
    {
        if(info_user->at(i).user == this->ui->username->text())
            if(info_user->at(i).name == this->ui->name->text())
                if(info_user->at(i).email == this->ui->email->text())
                {
                    if(this->ui->password->text() == nullptr)
                    {
                        this->ui->textBrowser->setText("enter your new password");
                        return;
                    }
                    if(this->ui->password_2->text() == nullptr)
                    {
                        this->ui->textBrowser->setText("fill all the blanks");
                        return;
                    }
                    if(this->ui->password_2->text().length() < 8)
                    {
                        this->ui->textBrowser->setText("pasword is too short.");
                        return;
                    }
                    if(this->ui->password_2->text() != this->ui->password->text())
                    {
                        this->ui->textBrowser->setText("passwords don't match");
                        return;
                    }
                    if(info_user->at(i).pass == this->ui->password->text())
                    {
                        this->ui->textBrowser->setText("enter a new pass");
                        return;
                    }
                    (*info_user)[i].pass=this->ui->password->text();
                    this->ui->textBrowser->setText("Done");
                    return;

                }
    }
    this->ui->textBrowser->setText("fill the blanks correctly");
}


void forget_pass::on_signup_clicked()
{
    MainWindow *page_m;
    close();
    page_m = new MainWindow(groups,info_book,info_user);
    page_m->show();
}

