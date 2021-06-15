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
}

admin::~admin()
{
    delete ui;
}

void admin::on_view_clicked()
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
                if(j!=0)
                    name.append(" ,");
                if(info_book->at(i).groups.at(j) != nullptr)
                    name.append(info_book->at(i).groups.at(j));
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

}


void admin::on_exit_clicked()
{
    MainWindow* page_m;
    hide();
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
    info_book->removeAt((this->ui->num->text().toInt() - 1));
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


void admin::on_edit_clicked()
{
    if(this->ui->num->text() == nullptr)
    {
        this->ui->show_3->setText("enter the number of the book");
        return;
    }
    int i = (this->ui->num->text().toInt() - 1);
    if(this->ui->name->text() != nullptr)
        (*info_book)[i].name = this->ui->name->text();
    if(this->ui->author->text() != nullptr)
        (*info_book)[i].author = this->ui->author->text();
    if(this->ui->publisher->text() != nullptr)
        (*info_book)[i].publisher = this->ui->publisher->text();
    int count = 0;
    for(int j = 0;j<3;j++)
    {
        if((*info_book)[i].groups.at(j) != nullptr)
            count++;
    }
    bool flag = false;
    if(count == 3)
    {
        (*info_book)[i].groups[0] = this->ui->group1->text();
        (*info_book)[i].groups[1] = this->ui->group2->text();
        (*info_book)[i].groups[2] = this->ui->group3->text();
        for(int j = 0; j<groups->count();j++)
            if(groups->at(j) ==  this->ui->group1->text())
                flag = true;
        if(!flag)
            groups->append(this->ui->group1->text());
        flag =false;
        for(int j = 0; j<groups->count();j++)
            if(groups->at(j) ==  this->ui->group2->text())
                flag = true;
        if(!flag)
            groups->append(this->ui->group2->text());
        flag = false;
        for(int j = 0; j<groups->count();j++)
            if(groups->at(j) ==  this->ui->group3->text())
                flag = true;
        if(!flag)
            groups->append(this->ui->group3->text());
    }
    else
    {
        if(this->ui->group1->text() != nullptr)
        {
                (*info_book)[i].groups[0] = this->ui->group1->text();
            for(int j = 0; j<groups->count();j++)
                if(groups->at(j) ==  this->ui->group1->text())
                    flag = true;
            if(!flag)
                groups->append(this->ui->group1->text());
        }
        flag = false;
        if(this->ui->group2->text() != nullptr)
        {
            if((*info_book)[i].groups[0] == nullptr)
                (*info_book)[i].groups[0] = this->ui->group2->text();
            else
                (*info_book)[i].groups[1] = this->ui->group2->text();
            for(int j = 0; j<groups->count();j++)
                if(groups->at(j) ==  this->ui->group2->text())
                    flag = true;
            if(!flag)
                groups->append(this->ui->group2->text());
        }
        flag = false;
        if(this->ui->group3->text() != nullptr)
        {
            if((*info_book)[i].groups[0] == nullptr)
                (*info_book)[i].groups[0] = this->ui->group3->text();
            else if((*info_book)[i].groups[1] == nullptr)
                (*info_book)[i].groups[1] = this->ui->group3->text();
            else
                (*info_book)[i].groups[2] = this->ui->group3->text();
            for(int j = 0; j<groups->count();j++)
                if(groups->at(j) ==  this->ui->group2->text())
                    flag = true;
            if(!flag)
                groups->append(this->ui->group2->text());
        }
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
    this->ui->show->clear();
    for(int i = 0;i<groups->count();i++)
        this->ui->show->append(groups->at(i));

}


void admin::on_ok_clicked()
{
    if(this->ui->search->text() == nullptr)
        return;
    if(!(((this->ui->publisher_2->isChecked())||(this->ui->name_2->isChecked()))||((this->ui->group->isChecked())||(this->ui->author_2->isChecked()))))
        this->ui->show->setText("check one of the buttons");
     this->ui->show->clear();
    if(this->ui->search->text().count() == 1)
    {
        this->ui->show->setText("you must use more letters");
    }
    bool flag = false;

    if(this->ui->group->isChecked())
    {
        int count = 0;
        QString search = this->ui->search->text();
        for(int i = 0; i < groups->count(); i++)
        {
            count = 0;
            if(groups->at(i).contains(search))
            {
                flag = true;
                this->ui->show->append(groups->at(i));
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
            }
        }
    }
    else if(this->ui->publisher_2->isChecked())
    {
        int count =0;
        QString search = this->ui->search->text();
        for(int i = 0; i < info_book->count();i++)
        {
            if(info_book->at(i).publisher.contains(search))
            {
                flag = true;
                count++;
                QString name=QString::number(count);
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
                        if(j!=0)
                            name.append(" ,");
                        if(info_book->at(i).groups.at(j) != nullptr)
                            name.append(info_book->at(i).groups.at(j));
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
    }
    else if(this->ui->author_2->isChecked())
    {
        int count =0;
        QString search = this->ui->search->text();
        for(int i = 0; i < info_book->count();i++)
        {
            if(info_book->at(i).author.contains(search))
            {
                flag = true;
                count++;
                QString name=QString::number(count);
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
                        if(j!=0)
                            name.append(" ,");
                        if(info_book->at(i).groups.at(j) != nullptr)
                            name.append(info_book->at(i).groups.at(j));
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
    }
    else if(this->ui->name_2->isChecked())
    {
        int count =0;
        QString search = this->ui->search->text();
        for(int i = 0; i < info_book->count();i++)
        {
            if(info_book->at(i).name.contains(search))
            {
                flag = true;
                count++;
                QString name=QString::number(count);
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
                        if(j!=0)
                            name.append(" ,");
                        if(info_book->at(i).groups.at(j) != nullptr)
                            name.append(info_book->at(i).groups.at(j));
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
    }
    if(!flag)
       this->ui->show_3->append("nothing found");
}

