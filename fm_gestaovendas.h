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

private slots:
    void on_tw_listavenda_itemSelectionChanged();

    void on_btn_filtrar_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::fm_gestaovendas *ui;
};

#endif // FM_GESTAOVENDAS_H
