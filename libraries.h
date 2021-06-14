#include <QString>
#include <QList>
#include<QFile>
#include"QTextStream"
class user_pass
{
public:
    QString user;
    QString pass;
    QString name;
    QString email;
    int num;
};
class books
{
public:
    QString name;
    QString author;
    QString publisher;
    QList<QString> groups;
    QString available = "yes";
    QString who="none";
};

