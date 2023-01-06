#ifndef FM_GESTAOVENDAS_H
#define FM_GESTAOVENDAS_H

#include <QDialog>

namespace Ui {
class fm_gestaovendas;
}

class fm_gestaovendas : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestaovendas(QWidget *parent = nullptr);
    ~fm_gestaovendas();

private:
    Ui::fm_gestaovendas *ui;
};

#endif // FM_GESTAOVENDAS_H
