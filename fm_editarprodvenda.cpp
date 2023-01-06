#include "fm_editarprodvenda.h"
#include "ui_fm_editarprodvenda.h"
#include "fm_nova_venda.h"

fm_editarprodvenda::fm_editarprodvenda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_editarprodvenda)
{
    ui->setupUi(this);
    ui->txt_editaproduto->setText(fm_nova_venda::g_prod);
     ui->txt_editapreco->setText(fm_nova_venda::g_valtotal);
      ui->txt_editaqtd->setText(fm_nova_venda::g_qtde);
}

fm_editarprodvenda::~fm_editarprodvenda()
{
    delete ui;
}

void fm_editarprodvenda::on_btn_editaconfirma_clicked()
{
    QString aux;
    fm_nova_venda::alterou = true;
    fm_nova_venda::g_qtde = ui->txt_editaqtd->text();
    aux = ui->txt_editapreco->text();
    std::replace(aux.begin(),aux.end(),',','.');
    fm_nova_venda::g_valtotal=aux;

    fm_nova_venda::total_g= QString::number(ui->txt_editaqtd->text().toDouble()* aux.toDouble());
    close();
}


void fm_editarprodvenda::on_btn_editacancela_clicked()
{
    fm_nova_venda::alterou= false;
    close();
}

