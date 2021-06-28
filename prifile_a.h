#ifndef PRIFILE_A_H
#define PRIFILE_A_H

#include <QDialog>

namespace Ui {
class prifile_a;
}

class prifile_a : public QDialog
{
    Q_OBJECT

public:
    explicit prifile_a(QWidget *parent = nullptr);
    ~prifile_a();

private:
    Ui::prifile_a *ui;
};

#endif // PRIFILE_A_H
