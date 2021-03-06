#include "user.h"
#include "ui_user.h"
#include "mainwindow.h"
#include "profile_u.h"
#include <QDate>
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
    int count = 0;
    for(int i = 0;i<info_book->count();i++)
    {
        if(info_book->at(i).available == "no")
            count++;
    }
    this->ui->amanat->setText(QString::number(count));
    this->ui->all->setText(QString::number(info_book->count()));
}

user::~user()
{
    delete ui;
}

void user::on_exit_clicked()
{
    MainWindow* page_m;
    close();
    page_m = new MainWindow(groups,info_book,info_user);
    page_m->show();
}


void user::on_view_clicked()
{
    this->ui->show->clear();
    for(int i=0;i<(*info_book).count();++i)
    {
        QString name=QString::number(i+1);
        name.append(".  name: ");
        name.append(info_book->at(i).name);
        name.append(" /author: ");
        name.append(info_book->at(i).author);
        name.append(" /publisher: ");
        name.append(info_book->at(i).publisher);
        name.append(" /groups: ");
        if(info_book->at(i).groups.at(0) == nullptr)
            name.append("-");
         else
        {
            for(int j = 0;j < 3;j++)
            {
                if(info_book->at(i).groups.at(j) != nullptr)
                {
                    if(j!=0)
                        name.append(" ,");
                    name.append(info_book->at(i).groups.at(j));
                }
                else
                    break;
            }
        }
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
            QDate today(QDate::currentDate());
            (*info_book)[i].from = today.toString("dd.MM.yyyy");
            (*info_book)[i].to = today.addDays(10).toString("dd.MM.yyyy");
            this->ui->nameofbook->clear();
            return;
        }
    }
    this->ui->show_2->setText("we don't have this book");
    this->ui->nameofbook->clear();
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
                this->ui->nameofbook->clear();

            return;
            }
            this->ui->show_2->setText("you didn't borrow this book");
            this->ui->nameofbook->clear();

            return;
        }
    }
    this->ui->show_2->setText("we don't have this book");
    this->ui->nameofbook->clear();

    return;
}
void user::on_profile_clicked()
{
    profile_u* page_p;
    close();
    page_p = new profile_u(index,groups,info_book,info_user);
    page_p->show();
}


void user::on_view_g_clicked()
{
    this->ui->show->clear();
    for(int i = 0;i<groups->count();i++)
        this->ui->show->append(groups->at(i));
}


void user::on_ok_clicked()
{

    if(this->ui->search->text() == nullptr)
        return;
    this->ui->show_3->clear();
    if(!(((this->ui->publisher_2->isChecked())||(this->ui->name_2->isChecked()))||((this->ui->group->isChecked())||(this->ui->author_2->isChecked()))))
        this->ui->show_3->setText("check one of the buttons");
    bool flag = false;
    if(this->ui->group->isChecked())
    {
        int count = 0;
        QString search = this->ui->search->text();
        for(int i = 0; i < groups->count(); i++)
        {
            count = 0;
            QList<QString> spliting = groups->at(i).split(" ");
            for(int j = 0;j<spliting.count();j++)
            {
                if(spliting.at(j).startsWith(search))
                {
                    flag= true;
                    QString group;
                    group.append("  *");
                    group.append(groups->at(i));
                    this->ui->show_3->append(group);
                    for(int j = 0;j<info_book->count();j++)
                    {
                        for(int z = 0;z < 3;z++)
                            if(info_book->at(j).groups.at(z) == groups->at(i))
                            {
                                count++;
                                QString name=QString::number(count);
                                name.append(".  name: ");
                                name.append(info_book->at(j).name);
                                name.append(" /author: ");
                                name.append(info_book->at(j).author);
                                name.append(" /publisher: ");
                                name.append(info_book->at(j).publisher);
                                if(info_book->at(j).available == "yes")
                                    name.append(" /available");
                                else
                                {
                                    name.append(" /not available");
                                }
                                this->ui->show_3->append(name);
                            }
                    }
                    break;
                }
            }
        }
    }
    else if(this->ui->publisher_2->isChecked())
    {
        int count = 0;
        QString search = this->ui->search->text();
        for(int i = 0; i < info_book->count(); i++)
        {
            QList<QString> spliting = info_book->at(i).publisher.split(" ");
            for(int j = 0;j<spliting.count();j++)
            {
                if(spliting.at(j).startsWith(search))
                {
                    flag= true;
                    count++;
                    QString name="  ";
                    name.append(QString::number(count));
                    name.append(".  name: ");
                    name.append(info_book->at(i).name);
                    name.append(" /author: ");
                    name.append(info_book->at(i).author);
                    name.append(" /publisher: ");
                    name.append(info_book->at(i).publisher);
                    name.append(" /groups: ");
                    if(info_book->at(i).groups.at(0) == nullptr)
                        name.append("-");
                    else
                    {
                        for(int j = 0;j < 3;j++)
                        {
                            if(info_book->at(i).groups.at(j) != nullptr)
                            {
                                if(j!=0)
                                    name.append(" ,");
                                name.append(info_book->at(i).groups.at(j));
                            }
                            else
                                break;
                        }
                    }
                    if(info_book->at(i).available == "yes")
                        name.append(" /available");
                    else
                        {
                            name.append(" /not available");
                        }
                        this->ui->show_3->append(name);
                    break;
                }
            }
        }
    }
    else if(this->ui->author_2->isChecked())
    {
        int count = 0;
        QString search = this->ui->search->text();
        for(int i = 0; i < info_book->count(); i++)
        {
            QList<QString> spliting = info_book->at(i).author.split(" ");
            for(int j = 0;j<spliting.count();j++)
            {
                if(spliting.at(j).startsWith(search))
                {
                    flag= true;
                    count++;
                    QString name="  ";
                    name.append(QString::number(count));
                    name.append(".  name: ");
                    name.append(info_book->at(i).name);
                    name.append(" /author: ");
                    name.append(info_book->at(i).author);
                    name.append(" /publisher: ");
                    name.append(info_book->at(i).publisher);
                    name.append(" /groups: ");
                    if(info_book->at(i).groups.at(0) == nullptr)
                        name.append("-");
                    else
                    {
                        for(int j = 0;j < 3;j++)
                        {
                            if(info_book->at(i).groups.at(j) != nullptr)
                            {
                                if(j!=0)
                                    name.append(" ,");
                                name.append(info_book->at(i).groups.at(j));
                            }
                            else
                                break;
                        }
                    }
                    if(info_book->at(i).available == "yes")
                        name.append(" /available");
                    else
                        {
                            name.append(" /not available");
                        }
                        this->ui->show_3->append(name);
                    break;
                }
            }
        }
    }
    else if(this->ui->name_2->isChecked())
    {
        int count = 0;
        QString search = this->ui->search->text();
        for(int i = 0; i < info_book->count(); i++)
        {
            QList<QString> spliting = info_book->at(i).name.split(" ");
            for(int j = 0;j<spliting.count();j++)
            {
                if(spliting.at(j).startsWith(search))
                {
                    flag= true;
                    count++;
                    QString name="  ";
                    name.append(QString::number(count));
                    name.append(".  name: ");
                    name.append(info_book->at(i).name);
                    name.append(" /author: ");
                    name.append(info_book->at(i).author);
                    name.append(" /publisher: ");
                    name.append(info_book->at(i).publisher);
                    name.append(" /groups: ");
                    if(info_book->at(i).groups.at(0) == nullptr)
                        name.append("-");
                    else
                    {
                        for(int j = 0;j < 3;j++)
                        {
                            if(info_book->at(i).groups.at(j) != nullptr)
                            {
                                if(j!=0)
                                    name.append(" ,");
                                name.append(info_book->at(i).groups.at(j));
                            }
                            else
                                break;
                        }
                    }
                    if(info_book->at(i).available == "yes")
                        name.append(" /available");
                    else
                        {
                            name.append(" /not available");
                        }
                        this->ui->show_3->append(name);
                    break;
                }
            }
        }
    }
    if(!flag)
        this->ui->show_3->append("nothing found");
}

