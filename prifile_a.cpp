#include "prifile_a.h"
#include "ui_prifile_a.h"

prifile_a::prifile_a(int index,QList<QString>* groups,QList<books>* info_book,QList<user_pass>* info_user,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::prifile_a)
{
    ui->setupUi(this);
    this->info_user = info_user;
    this->info_book = info_book;
    this->index = index;
    this->groups = groups;
    ui->amanat->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->amanat_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->amanat->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->amanat_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->amanat->verticalHeader()->hide();
    ui->amanat_3->verticalHeader()->hide();
    ui->name->setText((*info_user)[index].name);
    ui->username->setText((*info_user)[index].user);
    ui->email->setText((*info_user)[index].email);
    ui->password->setText("00000000");
}

prifile_a::~prifile_a()
{
    delete ui;
}

void prifile_a::on_back_clicked()
{
    admin* page_u;
    close();
    page_u = new admin(index,groups,info_book,info_user);
    page_u->show();
}


void prifile_a::on_exit_3_clicked()
{
    MainWindow* page_u;
    close();
    page_u = new MainWindow(groups,info_book,info_user);
    page_u->show();
}


void prifile_a::on_exit_5_clicked()
{
    int count = 0;
    if(this->ui->amanat_3->rowCount()!= 0)
       return;
    for(int i = 0;i<info_book->count();i++)
    {
        if(info_book->at(i).available == "yes")
            continue;
        this->ui->amanat_3->insertRow(count);
        QTableWidgetItem* x = new QTableWidgetItem(info_book->at(i).who);
        x->setTextAlignment(Qt::AlignCenter);
        this->ui->amanat_3->setItem(count,0,x);
        QTableWidgetItem* y = new QTableWidgetItem(info_book->at(i).name);
        y->setTextAlignment(Qt::AlignCenter);
        this->ui->amanat_3->setItem(count,1,y);
        QTableWidgetItem* z = new QTableWidgetItem(info_book->at(i).from);
        z->setTextAlignment(Qt::AlignCenter);
        this->ui->amanat_3->setItem(count,2,z);
        QTableWidgetItem* t = new QTableWidgetItem(info_book->at(i).to);
        t->setTextAlignment(Qt::AlignCenter);
        this->ui->amanat_3->setItem(count,3,t);
        count++;
     }
}


void prifile_a::on_exit_2_clicked()
{
    int count = 0;
    if(this->ui->amanat->rowCount()!= 0)
       return;
    for(int i = 0;i<info_user->count();i++)
    {
        if(i == index)
            continue;
        this->ui->amanat->insertRow(count);
        QTableWidgetItem* x = new QTableWidgetItem(info_user->at(i).user);
        x->setTextAlignment(Qt::AlignCenter);
        this->ui->amanat->setItem(count,0,x);
        QTableWidgetItem* y = new QTableWidgetItem(info_user->at(i).name);
        y->setTextAlignment(Qt::AlignCenter);
        this->ui->amanat->setItem(count,1,y);
        QTableWidgetItem* z = new QTableWidgetItem(info_user->at(i).email);
        z->setTextAlignment(Qt::AlignCenter);
        this->ui->amanat->setItem(count,2,z);
        count++;
     }
}



void prifile_a::on_exit_clicked()
{
    if(this->ui->username->text() != "Admin")
    {
        this->ui->textBrowser->setText("you can't change your username.");
        this->ui->username->setText("Admin");
        return;
    }
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
    if(this->ui->password->text() != "00000000")
    {
        if(this->ui->password_2->text() == nullptr)
        {
            this->ui->textBrowser->setText("for changing password you must fill repeat password too.");
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
        this->ui->password->setText("00000000");
        this->ui->password_2->clear();
    }
}

