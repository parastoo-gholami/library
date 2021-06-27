#include "profile_u.h"
#include "ui_profile_u.h"

profile_u::profile_u(int index,QList<QString>* groups,QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::profile_u)
{
    ui->setupUi(this);
    this->info_user = info_user;
    this->info_book = info_book;
    this->index = index;
    this->groups = groups;
    ui->amanat->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->amanat->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->amanat->verticalHeader()->hide();
    ui->name->setText((*info_user)[index].name);
    ui->username->setText((*info_user)[index].user);
    ui->email->setText((*info_user)[index].email);
    ui->password->setText("00000000");
}
profile_u::~profile_u()
{
    delete ui;
}

void profile_u::on_back_clicked()
{
    user* page_u;
    close();
    page_u = new user(index,groups,info_book,info_user);
    page_u->show();
}


void profile_u::on_exit_clicked()
{
    if(this->ui->name->text() != (*info_user)[index].name)
    {
        (*info_user)[index].name = this->ui->name->text();
        this->ui->textBrowser->setText("edited.");
    }
    if(this->ui->email->text() != (*info_user)[index].email)
    {
        (*info_user)[index].email = this->ui->email->text();
        this->ui->textBrowser->setText("edited.");
    }
    if(this->ui->username->text() != (*info_user)[index].user)
    {
        for(int j = 0;j<info_book->count();j++)
        {

            if(info_book->at(j).who==info_user->at(index).user)
                (*info_book)[j].who = this->ui->username->text();
        }
        (*info_user)[index].user = this->ui->username->text();
        this->ui->textBrowser->setText("edited.");

    }
    if(this->ui->password->text() != "00000000")
    {
        if(this->ui->password_2->text() == nullptr)
        {
            this->ui->textBrowser->setText("for changing password you must fill rpeat password too.");
            return;
        }
        if(this->ui->password->text().length() <8)
        {
            this->ui->textBrowser->setText("password is too short.");
            return;
        }
        if(this->ui->password_2->text()!=this->ui->password->text())
        {
            this->ui->textBrowser->setText("password doesn't match");
            return;
        }
        (*info_user)[index].pass = this->ui->password->text();
        this->ui->textBrowser->setText("edited");
    }
}


void profile_u::on_exit_3_clicked()
{
    MainWindow* page_u;
    close();
    page_u = new MainWindow(groups,info_book,info_user);
    page_u->show();
}


void profile_u::on_exit_2_clicked()
{
    int count = 0;
//    if(this->ui->amanat->rowCount()!= 0)
//        return;
    for(int i = 0;i<info_book->count();i++)
    {
        if(info_book->at(i).available == "yes")
            continue;
        if(info_book->at(i).who == info_user->at(index).user)
        {
            //this->ui->amanat->insertRow(ui->amanat->rowCount() + 1);
            QTableWidgetItem* x = new QTableWidgetItem(info_book->at(i).name);
            x->setTextAlignment(Qt::AlignCenter);
            this->ui->amanat->setItem(count,0,x);
            QTableWidgetItem* y = new QTableWidgetItem(info_book->at(i).author);
            y->setTextAlignment(Qt::AlignCenter);
            this->ui->amanat->setItem(count,1,y);
            QTableWidgetItem* z = new QTableWidgetItem(info_book->at(i).from);
            z->setTextAlignment(Qt::AlignCenter);
            this->ui->amanat->setItem(count,2,z);
            QTableWidgetItem* t = new QTableWidgetItem(info_book->at(i).to);
            t->setTextAlignment(Qt::AlignCenter);
            this->ui->amanat->setItem(count,3,t);

            count++;
        }

    }
}

