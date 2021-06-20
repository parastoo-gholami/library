#include "registration.h"
#include "ui_registration.h"
#include "mainwindow.h"
registration::registration(QList<QString>* groups,QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registration)
{
    ui->setupUi(this);
    this->info_user = info_user;
    this->info_book = info_book;
    this->groups = groups;
}

registration::~registration()
{
    delete ui;
}

void registration::on_signup_clicked()
{

    if(this->ui->name->text() == nullptr)
    {
        this->ui->textBrowser->setText("please fill all the blanks.");
        return;
    }
    if(this->ui->username->text() == nullptr)
    {
        this->ui->textBrowser->setText("please fill all the blanks.");
        return;
    }
    if(this->ui->email->text() == nullptr)
    {
        this->ui->textBrowser->setText("please fill all the blanks.");
        return;
    }
    if(this->ui->password->text() == nullptr)
    {
        this->ui->textBrowser->setText("please fill all the blanks.");
        return;
    }
    if(this->ui->repassword->text() == nullptr)
    {
        this->ui->textBrowser->setText("please fill all the blanks.");
        return;
    }
    if((this->ui->password->text().length())<8)
    {
        this->ui->textBrowser->setText("password is too short");
        return;
    }
    if((this->ui->username->text().length())<5)
    {
        this->ui->textBrowser->setText("username is too short");
        return;
    }
    if(this->ui->repassword->text() != this->ui->password->text())
    {
        this->ui->textBrowser->setText("password doesn't match.");
        return;
    }
    if(!(this->ui->agree->isChecked()))
    {
        this->ui->textBrowser->setText("check the agreement.");
        return;
    }

    user_pass tmp;
    tmp.user = this->ui->username->text();
    for(int i=0;i<(*info_user).count();++i)
    {
        if(info_user->at(i).user == tmp.user)
        {
            this->ui->textBrowser->setText("choose another username");
            return;
        }
    }

    tmp.pass = this->ui->password->text();
    tmp.email = this->ui->email->text();
    tmp.name = this->ui->name->text();
    tmp.num = 0;
    info_user->append(tmp);
    MainWindow* page_m;
    hide();
    page_m = new MainWindow(groups,info_book,info_user);
    page_m->show();
}



void registration::on_exit_clicked()
{
    MainWindow* page_m;
    hide();
    page_m = new MainWindow(groups,info_book,info_user);
    page_m->show();
}

