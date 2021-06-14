#include "mainwindow.h"

#include <QApplication>

QList<user_pass> info_user;
QList<books> info_book;
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
        info_book.append(b);
    }
    file.close();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    load_up();
    load_b();
    MainWindow w(&info_book,&info_user);
    w.show();
    return a.exec();

}
//void save_up()
//{
//    QFile file("user_pass.txt");
//    if(!file.open(QFile::WriteOnly|QFile::Text))
//        return;
//    QTextStream qts(&file);
//    for(int i = 0;i<info_user.count();i++)
//    {
//        qts<<info_user.at(i).user + "\n";
//        qts<<info_user.at(i).pass + "\n";
//        qts<<info_user.at(i).name + "\n";
//        qts<<info_user.at(i).email + "\n";
//        for(int j = 0;j<=info_user.at(i).num.count();j++)
//        {
//            QString s;
//            if(j!=info_user.at(i).num.count())
//                s = QString::number(info_user.at(i).num.at(j));
//            else
//                s = "0";
//            qts<<s+"\n";

//        }
//    }
//    file.close();
//}
//void save_b()
//{
//    QString tmp;
//    QFile file("books.txt");
//    if(!file.open(QFile::Text | QFile::WriteOnly))
//        return;
//    QTextStream qts(&file);
//    for(int i = 0;i<info_book.count();i++)
//    {
//        tmp=QString::number(info_book.at(i).num);
//        qts<<tmp + "\n";
//        qts<<info_book.at(i).name + "\n";
//        qts<<info_book.at(i).author + "\n";
//        qts<<info_book.at(i).publisher + "\n";
//        for(int j = 0;j<=info_book.at(i).groups.count();j++)
//        {
//            if(j == info_book.at(i).groups.count())
//                qts<<"end\n";
//            else
//                qts<<info_book.at(i).groups.at(j)+"\n";
//        }
//        qts<<info_book.at(i).available + "\n";
//        qts<<info_book.at(i).who + "\n";
//    }
//    file.close();
//}
