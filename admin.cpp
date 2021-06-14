#include "admin.h"
#include "ui_admin.h"
#include "mainwindow.h"
admin::admin(int index,QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    this->info_user = info_user;
    this->info_book = info_book;
    this->index = index;
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
    page_m = new MainWindow(info_book,info_user);
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
    if(this->ui->group1->text() != nullptr)
    {
            (*info_book)[i].groups[0] = this->ui->group1->text();
    }
    if(this->ui->group2->text() != nullptr)
    {
            (*info_book)[i].groups[1] = this->ui->group2->text();
    }
    if(this->ui->group3->text() != nullptr)
    {
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

