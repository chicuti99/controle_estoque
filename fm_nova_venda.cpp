#include "fm_nova_venda.h"
#include "ui_fm_nova_venda.h"
#include <QtSql>
#include "fm_editarprodvenda.h"
#include "fm_principal.h"
#include "variaveis_globais.h"

static QSqlDatabase bancodedados=QSqlDatabase::addDatabase("QSQLITE");

QString fm_nova_venda::g_idprod;
QString fm_nova_venda::g_prod;
QString fm_nova_venda::g_qtde;
QString fm_nova_venda::g_valtotal;
QString fm_nova_venda::total_g;
bool fm_nova_venda::alterou;

fm_nova_venda::fm_nova_venda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_nova_venda)
{
    ui->setupUi(this);
    QSqlDatabase bancodedados=QSqlDatabase::addDatabase("QSQLITE");
    bancodedados.setDatabaseName("C:/Users/Usuario/Documents/estudos/c++/QTcreator/controle_estoque/db.db");
    if(!bancodedados.open()) {
         QMessageBox::about(this,"erro","Erro ao abrir banco de dados");
     }

    ui->tw_listaprod->setColumnCount(5);
    ui->tw_listaprod->setColumnWidth(0,100);
    ui->tw_listaprod->setColumnWidth(1,100);
    ui->tw_listaprod->setColumnWidth(2,100);
    ui->tw_listaprod->setColumnWidth(3,100);
    ui->tw_listaprod->setColumnWidth(4,100);
    QStringList cabecalhos ={"codigo","produtos","valor un","Qtde","total"};
    ui->tw_listaprod->setHorizontalHeaderLabels(cabecalhos);
    ui->tw_listaprod->setStyleSheet("QTableView{selection-background-color: blue;}");
    ui->tw_listaprod->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tw_listaprod->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tw_listaprod->verticalHeader()->setVisible(false);
    ui->txt_codprod->setFocus();

    contlihas = 0;
}

fm_nova_venda::~fm_nova_venda()
{
    delete ui;
}

void fm_nova_venda::on_txt_codprod_returnPressed()
{
    QSqlQuery query;
    QString id = ui->txt_codprod->text();
    double total;
    query.prepare("select id_produtos,produto,valor_venda from tb_produtos where id_produtos = "+id);
    if(query.exec()){
        query.first();
        if(query.value(0).toString()!= ""){
            ui->tw_listaprod->insertRow(contlihas);
            ui->tw_listaprod->setItem(contlihas,0,new QTableWidgetItem(query.value(0).toString()));
            ui->tw_listaprod->setItem(contlihas,1,new QTableWidgetItem(query.value(1).toString()));
            ui->tw_listaprod->setItem(contlihas,2,new QTableWidgetItem(query.value(2).toString()));
            ui->tw_listaprod->setItem(contlihas,3,new QTableWidgetItem(ui->txt_qtde->text()));
            total = ui->txt_qtde->text().toDouble()*query.value(2).toDouble();
            ui->tw_listaprod->setItem(contlihas,4,new QTableWidgetItem(QString::number(total)));
            ui->tw_listaprod->setRowHeight(contlihas,20);
            contlihas++;

            ui->lb_total->setText("R$ "+QString::number(calculatotal(ui->tw_listaprod,4)));
        }

        else{
            QMessageBox::warning(this,"erro","produto não encontrado");
        }

    }
    else{
        QMessageBox::warning(this,"erro","erro ao inserir novo produto");
    }


}


void fm_nova_venda::resetacampos(){
    ui->txt_codprod->clear();
    ui->txt_qtde->setText("1");
    ui->txt_codprod->setFocus();
}


void fm_nova_venda::removelinhas(QTableWidget *tw){
    while(tw->rowCount()>0){
        tw->removeRow(0);
    }
}



double fm_nova_venda::calculatotal(QTableWidget *tw,int coluna ){
    int totalinhas;
    double total;

    totalinhas = tw->rowCount();
    for(int i = 0; i < totalinhas ;i++){
        total += tw->item(i,coluna)->text().toDouble();


    }
    return total;
}

void fm_nova_venda::on_btn_excluirprod_clicked()
{
    if(ui->tw_listaprod->currentColumn() != -1){
        QMessageBox::StandardButton opc = QMessageBox::question(this,"Exclusão","Deseja excluir o produto",QMessageBox::Yes|QMessageBox::No);
        if(opc = QMessageBox::Yes){
            ui->tw_listaprod->removeRow(ui->tw_listaprod->currentRow());
            ui->lb_total->setText("R$ "+QString::number(calculatotal(ui->tw_listaprod,4)));
            contlihas--;
        }

    }

    else{
        QMessageBox::warning(this,"erro","selecione um produto primeiro");
    }
}


void fm_nova_venda::on_btn_editprod_clicked()
{
    if(ui->tw_listaprod->currentColumn() != -1){
        int linha = ui->tw_listaprod->currentRow();
        g_idprod = ui->tw_listaprod->item(linha,0)->text();
        g_prod = ui->tw_listaprod->item(linha,1)->text();
        g_valtotal = ui->tw_listaprod->item(linha,2)->text();
        g_qtde = ui->tw_listaprod->item(linha,3)->text();
        fm_editarprodvenda f_editarprodvenda;
        f_editarprodvenda.exec();

        if(alterou){
            ui->tw_listaprod->item(linha,2)->setText(g_valtotal);
            ui->tw_listaprod->item(linha,3)->setText(g_qtde);
            ui->tw_listaprod->item(linha,4)->setText(total_g);
            ui->lb_total->setText("R$ "+QString::number(calculatotal(ui->tw_listaprod,4)));
    }
}
}


void fm_nova_venda::on_btn_final_clicked()
{
    if(ui->tw_listaprod->rowCount() >0){
        int idVenda;
        QString msgfimvenda;
        double total = calculatotal(ui->tw_listaprod,4);
        QString data = QDate::currentDate().toString("yyyy-MM-dd");
        QString hora =QTime::currentTime().toString("hh:mm:ss");
        QSqlQuery query;
        query.prepare("insert into tb_vendas(data_venda,hora_venda,id_colaborador,valor_total,id_tipo_pagamento) values ('"+data+"','"+hora+"','"+QString::number(variaveis_globais::id_colab)+"','"+QString::number(total)+"',1)");
        if(!query.exec()){
            QMessageBox::warning(this,"erro","Erro ao registrar nova venda");
        }

        else{
            query.exec("select id_vendas from tb_vendas order by id_vendas desc limit 1 ");
            query.exec();
            query.first();
            idVenda = query.value(0).toInt();
            msgfimvenda = "ID venda "+ QString::number(idVenda)+"\nValor total R$"+QString::number(total);

            int totalinhas = ui->tw_listaprod->rowCount();
            int linha = 0;

            while(linha < totalinhas){
                QString prod= ui->tw_listaprod->item(linha,1)->text();
                QString Qtde= ui->tw_listaprod->item(linha,3)->text();
                QString valuni = ui->tw_listaprod->item(linha,2)->text();
                QString valtot = ui->tw_listaprod->item(linha,4)->text();
                query.prepare("insert into tb_vendidos (id_venda,produto,qtde,valor_un,valor_total) values('"+QString::number(idVenda)+"','"+prod+"','"+Qtde+"','"+valuni+"','"+valtot+"')");
                query.exec();
                linha++;
            }

            QMessageBox::warning(this,"erro",msgfimvenda);
            resetacampos();
            removelinhas(ui->tw_listaprod);
            ui->lb_total->setText("R$: 0.00");

        }
    }

    else{
        QMessageBox::warning(this,"erro","Não existem produtos nessa venda\nPrimeiro adicione produtos nessa venda");
    }
}

