#include "mainwindow.h"

#include <QApplication>

QList<user_pass> info_user;
QList<books> info_book;
QList<QString> groups;
void load_gp()
{
    QString tmp;
    QFile file("groups.txt");
    if(!file.open(QFile::Text | QFile::ReadOnly))
        return;
    QTextStream qts(&file);
    while(!qts.atEnd())
    {
        tmp=qts.readLine();
        groups.append(tmp);
    }
    file.close();
}
void load_up()
{
    QFile file("user_pass.txt");
    if(!file.open(QFile::Text | QFile::ReadOnly))
        return;
    QTextStream qts(&file);
    while(!qts.atEnd())
    {
        user_pass up;
        up.user = qts.readLine();
        up.pass = qts.readLine();
        up.name = qts.readLine();
        up.email = qts.readLine();
        up.num = qts.readLine().toInt();
        info_user.append(up);
    }
    file.close();
}
void load_b()
{
    QFile file("books.txt");
    if(!file.open(QFile::Text | QFile::ReadOnly))
        return;
    QTextStream qts(&file);
    while(!qts.atEnd())
    {
        books b;
        b.name = qts.readLine();
        b.author = qts.readLine();
        b.publisher = qts.readLine();
        for(int i = 0;i < 3;i++)
        {
            b.groups.append(qts.readLine());
        }
        b.available = qts.readLine();
        b.who = qts.readLine();
        b.from = qts.readLine();
        b.to = qts.readLine();
        info_book.append(b);
    }
    file.close();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    load_up();
    load_b();
    load_gp();
    MainWindow w(&groups,&info_book,&info_user);
    w.show();
    return a.exec();

}

