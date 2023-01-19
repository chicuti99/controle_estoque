#ifndef FM_NOVA_VENDA_H
#define FM_NOVA_VENDA_H

#include <QDialog>
#include<QTableWidget>
#include <QMessageBox>

namespace Ui {
class fm_nova_venda;
}

class fm_nova_venda : public QDialog
{
    Q_OBJECT

public:
    explicit fm_nova_venda(QWidget *parent = nullptr);
    ~fm_nova_venda();
    int contlihas;
    void resetacampos();
    double calculatotal(QTableWidget *tw, int coluna);
    static QString g_idprod,g_prod,g_qtde,g_valtotal,total_g;
    static bool alterou;
    void removelinhas(QTableWidget *tw);

private slots:
    void on_txt_codprod_returnPressed();

    void on_btn_excluirprod_clicked();

    void on_btn_editprod_clicked();

    void on_btn_final_clicked();

private:
    Ui::fm_nova_venda *ui;
};

#endif // FM_NOVA_VENDA_H
