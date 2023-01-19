#ifndef FM_GESTAOCOLABORADORES_H
#define FM_GESTAOCOLABORADORES_H

#include <QDialog>

namespace Ui {
class fm_gestaocolaboradores;
}

class fm_gestaocolaboradores : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestaocolaboradores(QWidget *parent = nullptr);
    ~fm_gestaocolaboradores();

private slots:
    void on_btn_novocolab_clicked();

    void on_btn_gravarnovocolab_clicked();

    void on_btn_cancelarnovo_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_tw_ge_listacolab_itemSelectionChanged();

    void on_btn_ge_filtrar_clicked();

    void on_btn_ge_salvar_clicked();

    void on_btn_ge_excluir_clicked();

private:
    Ui::fm_gestaocolaboradores *ui;
};

#endif // FM_GESTAOCOLABORADORES_H
