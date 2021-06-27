#include "admin.h"
#include "ui_admin.h"
#include "mainwindow.h"
admin::admin(int index,QList<QString>* groups,QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    this->info_user = info_user;
    this->info_book = info_book;
    this->groups = groups;
    this->index = index;
    int count = 0;
    for(int i = 0;i<info_book->count();i++)
    {
        if(info_book->at(i).available == "no")
            count++;
    }
    this->ui->amanat->setText(QString::number(count));
    this->ui->all->setText(QString::number(info_book->count()));
}

admin::~admin()
{
    delete ui;
}

void admin::on_view_clicked()
{
    this->ui->show_3->clear();
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
        {
            name.append(" /not available-borrowed by ");
            name.append(info_book->at(i).who);
        }
        this->ui->show->append(name);
    }
}


void admin::on_add_clicked()
{
    if(this->ui->name->text() == nullptr)
    {
        this->ui->show_3->setText("name of the book?");
        return;
    }
    if(this->ui->author->text() == nullptr)
    {
        this->ui->show_3->setText("author of the book?");
        return;
    }
    if(this->ui->publisher->text() == nullptr)
    {
        this->ui->show_3->setText("puclisher of the book?");
        return;
    }
    for(int i = 0; i<info_book->length();i++)
    {
        if(info_book->at(i).name == this->ui->name->text())
            if(info_book->at(i).author == this ->ui->author->text())
                if(info_book->at(i).publisher == this->ui->publisher->text())
                {
                    this->ui->show_3->setText("you already add this book");
                    return;
                }
    }
    if((this->ui->group1->text()!= nullptr)&&(this->ui->group2->text()!= nullptr))
        if((this->ui->group1->text()) ==(this->ui->group2->text()))
        {
            this->ui->show_3->setText("name of groups can be the same");
            return;
        }
    if((this->ui->group1->text()!= nullptr)&&(this->ui->group3->text()!= nullptr))
        if((this->ui->group1->text()) ==(this->ui->group3->text()))
        {
            this->ui->show_3->setText("name of groups can be the same");
            return;
        }
    if((this->ui->group3->text()!= nullptr)&&(this->ui->group2->text()!= nullptr))
        if((this->ui->group3->text()) ==(this->ui->group2->text()))
        {
            this->ui->show_3->setText("name of groups can be the same");
            return;
        }
    books tmp;
    tmp.who = "none";
    tmp.author = this->ui->author->text();
    tmp.available = "yes";
    tmp.name = this->ui->name->text();
    tmp.publisher =this->ui->publisher->text();
    tmp.groups.append(this->ui->group1->text());
    tmp.groups.append(this->ui->group2->text());
    tmp.groups.append(this->ui->group3->text());
    info_book->append(tmp);
    this->ui->show_3->setText("done");


    bool flag = false;
    if(this->ui->group1->text()!= nullptr)
    {
        for(int j = 0; j<groups->count();j++)
            if(groups->at(j) ==  this->ui->group1->text())
                flag = true;
        if(!flag)
            groups->append(this->ui->group1->text());
    }
    flag = false;
    if(this->ui->group2->text()!= nullptr)
    {
        for(int j = 0; j<groups->count();j++)
            if(groups->at(j) ==  this->ui->group2->text())
                flag = true;
        if(!flag)
            groups->append(this->ui->group2->text());
    }
    flag = false;
    if(this->ui->group3->text()!= nullptr)
    {
        for(int j = 0; j<groups->count();j++)
            if(groups->at(j) ==  this->ui->group3->text())
                flag = true;
        if(!flag)
            groups->append(this->ui->group3->text());
    }
    this->ui->num->clear();
    this->ui->name->clear();
    this->ui->author->clear();
    this->ui->num->clear();
    this->ui->publisher->clear();
    this->ui->group1->clear();
    this->ui->group2->clear();
    this->ui->group3->clear();
    int count = 0;
    for(int i = 0;i<info_book->count();i++)
    {
        if(info_book->at(i).available == "no")
            count++;
    }
    this->ui->amanat->setText(QString::number(count));
    this->ui->all->setText(QString::number(info_book->count()));
}


void admin::on_exit_clicked()
{
    MainWindow* page_m;
    close();
    page_m = new MainWindow(groups,info_book,info_user);
    page_m->show();
}


void admin::on_remove_clicked()
{
    if(this->ui->num->text() == nullptr)
    {
        this->ui->show_3->setText("enter the number of the book");
        return;
    }
    int book_index;
    bool flag = false;
    book_index =this->ui->num->text().toInt() - 1;
    for(int j = 0; j < 3; j++)
    {
        if((*info_book)[book_index].groups.at(j) ==nullptr)
            break;
        for(int i = 0; i < info_book->count(); i++)
        {
            if(i == book_index)
                continue;
            for(int z = 0; z < 3; z++)
            {
                if((*info_book)[i].groups.at(z) ==nullptr)
                    break;
                if((*info_book)[book_index].groups.at(j) == (*info_book)[i].groups.at(z))
                    flag = true;
            }
        }
        if(flag == false)
            for(int z = 0;z<groups->count();z++)
            {
                if((*info_book)[book_index].groups[j] == groups->at(z))
                    groups->removeAt(z);
            }
        flag = false;
    }
    info_book->removeAt((book_index));
    this->ui->show_3->setText("press view to update the list");
    this->ui->num->clear();
    this->ui->name->clear();
    this->ui->author->clear();
    this->ui->num->clear();
    this->ui->publisher->clear();
    this->ui->group1->clear();
    this->ui->group2->clear();
    this->ui->group3->clear();
    int count = 0;
    for(int i = 0;i<info_book->count();i++)
    {
        if(info_book->at(i).available == "no")
            count++;
    }
    this->ui->amanat->setText(QString::number(count));
    this->ui->all->setText(QString::number(info_book->count()));
}


void admin::on_edit_clicked()
{
    if(this->ui->num->text() == nullptr)
    {
        this->ui->show_3->setText("enter the number of the book");
        return;
    }
    int i = (this->ui->num->text().toInt() - 1);
    if(this->ui->name->text() != info_book->at(i).name)
        (*info_book)[i].name = this->ui->name->text();
    if(this->ui->author->text() != info_book->at(i).author)
        (*info_book)[i].author = this->ui->author->text();
    if(this->ui->publisher->text() != info_book->at(i).publisher)
        (*info_book)[i].publisher = this->ui->publisher->text();
    if(this->ui->group1->text() != info_book->at(i).groups[0])
    {
        bool flag = false;
            for(int s = 0; s < info_book->count(); s++)
            {
                if(s == i)
                    continue;
                for(int z = 0; z < 3; z++)
                {
                if((*info_book)[s].groups.at(z) ==nullptr)
                    break;
                if((*info_book)[i].groups.at(0) == (*info_book)[s].groups.at(z))
                    flag = true;
                }
            }
            if(flag == false)
                for(int z = 0;z<groups->count();z++)
                {
                if((*info_book)[i].groups[0] == groups->at(z))
                    groups->removeAt(z);
                }
        (*info_book)[i].groups[0] = this->ui->group1->text();
    }
    if(this->ui->group2->text() != info_book->at(i).groups[1])
    {
        bool flag = false;
            for(int s = 0; s < info_book->count(); s++)
            {
                if(s == i)
                    continue;
                for(int z = 0; z < 3; z++)
                {
                if((*info_book)[s].groups.at(z) ==nullptr)
                    break;
                if((*info_book)[i].groups.at(1) == (*info_book)[s].groups.at(z))
                    flag = true;
                }
            }
            if(flag == false)
                for(int z = 0;z<groups->count();z++)
                {
                if((*info_book)[i].groups[1] == groups->at(z))
                    groups->removeAt(z);
                }
        (*info_book)[i].groups[1] = this->ui->group2->text();
    }
    if(this->ui->group3->text() != info_book->at(i).groups[2])
    {
        bool flag = false;
            for(int s = 0; s < info_book->count(); s++)
            {
                if(s == i)
                    continue;
                for(int z = 0; z < 3; z++)
                {
                if((*info_book)[s].groups.at(z) ==nullptr)
                    break;
                if((*info_book)[i].groups.at(2) == (*info_book)[s].groups.at(z))
                    flag = true;
                }
            }
            if(flag == false)
                for(int z = 0;z<groups->count();z++)
                {
                if((*info_book)[i].groups[0] == groups->at(z))
                    groups->removeAt(z);
                }
        (*info_book)[i].groups[2] = this->ui->group3->text();
    }

    this->ui->show_3->setText("done");
    this->ui->num->clear();
    this->ui->name->clear();
    this->ui->author->clear();
    this->ui->num->clear();
    this->ui->publisher->clear();
    this->ui->group1->clear();
    this->ui->group2->clear();
    this->ui->group3->clear();

}


void admin::on_view_g_clicked()
{
    this->ui->show_3->clear();
    this->ui->show->clear();
    for(int i = 0;i<groups->count();i++)
        this->ui->show->append(groups->at(i));

}


void admin::on_ok_clicked()
{
    if(this->ui->search->text() == nullptr)
        return;
    this->ui->show->clear();
    if(!(((this->ui->publisher_2->isChecked())||(this->ui->name_2->isChecked()))||((this->ui->group->isChecked())||(this->ui->author_2->isChecked()))))
    {

        this->ui->show->setText("check one of the buttons");
        return;
    }
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
                                    name.append(" /not available-borrowed by ");
                                    name.append(info_book->at(j).who);
                                }
                                this->ui->show->append(name);
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
                        name.append(" /not available-borrowed by ");
                        name.append(info_book->at(j).who);
                    }
                        this->ui->show->append(name);
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
                        name.append(" /not available-borrowed by ");
                        name.append(info_book->at(j).who);
                    }
                        this->ui->show->append(name);
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
                        name.append(" /not available-borrowed by ");
                        name.append(info_book->at(j).who);
                    }
                        this->ui->show->append(name);
                    break;
                }
            }
        }
    }
    if(!flag)
        this->ui->show->append("nothing found");
}


void admin::on_num_textChanged(const QString &arg1)
{

    if(arg1 == nullptr)
    {
        this->ui->name->clear();
        this->ui->author->clear();
        this->ui->publisher->clear();
        this->ui->group1->clear();
        this->ui->group2->clear();
        this->ui->group3->clear();
        return;
    }
    bool isnum;
    int value = arg1.toInt(&isnum);
    if(isnum)
    {
        if(arg1.toInt() > info_book->count())
        {
            this->ui->show_3->setText("invalid number");
            this->ui->num->clear();
            return;
        }
        this->ui->name->setText(info_book->at(value - 1).name);
        this->ui->author->setText(info_book->at(value - 1).author);
        this->ui->publisher->setText(info_book->at(value - 1).publisher);
        this->ui->group1->setText(info_book->at(value - 1).groups.at(0));
        this->ui->group2->setText(info_book->at(value - 1).groups.at(1));
        this->ui->group3->setText(info_book->at(value - 1).groups.at(2));
    }
    else
    {
        this->ui->show_3->setText("not number");
        this->ui->num->clear();
        return;
    }


}

