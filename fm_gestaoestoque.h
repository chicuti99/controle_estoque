#ifndef FM_GESTAOESTOQUE_H
#define FM_GESTAOESTOQUE_H

#include <QDialog>
#include <QMessageBox>
#include<QTableWidget>
#include <QtSql>
#include <QMessageBox>
namespace Ui {
class fm_gestaoestoque;
}

class fm_gestaoestoque : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestaoestoque(QWidget *parent = nullptr);
    ~fm_gestaoestoque();


private slots:
    void on_btn_novoproduto_clicked();

    void on_btn_gravar_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tw_ge_produtos_itemSelectionChanged();

    void on_btn_ge_gravar_clicked();

    void on_btn_ge_excluir_clicked();

    void on_btn_ge_filtrar_clicked();

private:
    Ui::fm_gestaoestoque *ui;
};

#endif // FM_GESTAOESTOQUE_H
