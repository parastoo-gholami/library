#include "prifile_a.h"
#include "ui_prifile_a.h"

prifile_a::prifile_a(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::prifile_a)
{
    ui->setupUi(this);
}

prifile_a::~prifile_a()
{
    delete ui;
}
