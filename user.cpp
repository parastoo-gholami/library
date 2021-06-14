#include "user.h"
#include "ui_user.h"
#include "mainwindow.h"
#include "profile.h"
user::user(int index,QList<QString>* groups,QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user)
{
    ui->setupUi(this);
    this->info_user = info_user;
    this->info_book = info_book;
    this->index = index;
    this->groups = groups;
    this->ui->welcom->setText(info_user->at(index).user);
}

user::~user()
{
    delete ui;
}

void user::on_exit_clicked()
{
    MainWindow* page_m;
    hide();
    page_m = new MainWindow(groups,info_book,info_user);
    page_m->show();
}


void user::on_view_clicked()
{
    this->ui->show->clear();
    for(int i=0;i<(*info_book).count();++i)
    {
        QString name="name: ";
        name.append(info_book->at(i).name);
        name.append(" /author: ");
        name.append(info_book->at(i).author);
        name.append(" /publisher: ");
        name.append(info_book->at(i).publisher);
        if(info_book->at(i).available == "yes")
            name.append(" /available");
        else
            name.append(" /not available");
        this->ui->show->append(name);
    }
}

void user::on_borrow_clicked()
{
    if(info_user->at(index).num>5)
    {
        this->ui->show_2->setText("you can only borrow 5 books");
        return;
    }
    for(int i=0;i<(*info_book).count();++i)
    {
        if(info_book->at(i).name == this->ui->nameofbook->text())
        {
            if((*info_book)[i].available == "no")
            {
                this->ui->show_2->setText("this book is not available");
                return;
            }
            (*info_book)[i].available = "no";
            this->ui->show_2->setText("done");
            (*info_user)[index].num++;
            (*info_book)[i].who = info_user->at(index).user;
            return;
        }
    }
    this->ui->show_2->setText("we don't have this book");
    return;
}


void user::on_returnbook_clicked()
{
    if(this->ui->nameofbook->text() == nullptr)
        return;
    for(int i=0;i<info_book->count();i++)
    {
        if(info_book->at(i).name == this->ui->nameofbook->text())
        {

            if(info_book->at(i).who == (*info_user)[index].user)
            {
                (*info_book)[i].available = "yes";
                (*info_user)[index].num--;
                (*info_book)[i].who = "none";
                this->ui->show_2->setText("done");
            return;
            }
            this->ui->show_2->setText("you didn't borrow this book");
            return;
        }
    }
    this->ui->show_2->setText("we don't have this book");
    return;
}
void user::on_profile_clicked()
{
    profile* page_p;
    hide();
    page_p = new profile();
    page_p->show();
}

