#include "mainwindow.h"

#include <QApplication>

QList<user_pass> info_user;
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
        info_user.append(up);
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(&info_user);
    w.show();
    return a.exec();
}
