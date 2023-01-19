#include "fm_gestaoestoque.h"
#include "ui_fm_gestaoestoque.h"
#include <QtSql>
#include <QMessageBox>
#include "funcoes_globais.h"
//#include "fm_log.h"

static QSqlDatabase bancodedados=QSqlDatabase::addDatabase("QSQLITE");

fm_gestaoestoque::fm_gestaoestoque(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_gestaoestoque)
{
    ui->setupUi(this);
    QSqlDatabase bancodedados=QSqlDatabase::addDatabase("QSQLITE");
        bancodedados.setDatabaseName("C:/Users/Usuario/Documents/estudos/c++/QTcreator/controle_estoque/db.db");
       if(!bancodedados.open()) {
            QMessageBox::about(this,"erro","Erro ao abrir banco de dados");
        }

       else{
           QSqlQuery query;
           query.prepare("select * from tb_produtos");
           if(query.exec()){


           }
           else{
               QMessageBox::warning(this,"erro","erro ao listar produtos");
           }
       }
       ui->tw_ge_produtos->setColumnCount(2);
       ui->tabWidget->setCurrentIndex(0);
}

fm_gestaoestoque::~fm_gestaoestoque()
{
    delete ui;
    bancodedados.close();
}

void fm_gestaoestoque::on_btn_novoproduto_clicked()
{
    ui->txt_codigo->clear();
    ui->txt_compra->clear();
    ui->txt_descricao->clear();
    ui->txt_fornecedor->clear();
    ui->txt_venda->clear();
    ui->txt_estoque->clear();

    ui->txt_codigo->setFocus();
}


void fm_gestaoestoque::on_btn_gravar_clicked()
{
    /*QSqlDatabase bancodedados=QSqlDatabase::addDatabase("QSQLITE");
    bancodedados.setDatabaseName("C:/Users/Usuario/Documents/estudos/c++/QTcreator/controle_estoque/db.db");
   if(!bancodedados.open()) {
        QMessageBox::about(this,"erro","Erro ao abrir banco de dados");
    }*/


       QString aux;
       aux = ui->txt_compra->text();
       std::replace(aux.begin(),aux.end(),',','.');
       QString codigo = ui->txt_codigo->text();
       QString descricao = ui->txt_descricao->text();
       QString compra = aux;

       aux = ui->txt_venda->text();
       std::replace(aux.begin(),aux.end(),',','.');
       QString estoque = ui->txt_estoque->text();
       QString fornecedor = ui->txt_fornecedor->text();
       QString venda  = aux;



        QSqlQuery query;
        query.prepare("insert into tb_produtos (id_produtos,produto,id_fornecedor,qtde_estoque,valor_compra,valor_venda) values "
                      "("+QString::number(codigo.toInt())+",'"+descricao+"',"+QString::number(fornecedor.toInt())+","+QString::number(estoque.toInt())+","+QString::number(compra.toFloat())+","+QString::number(venda.toFloat())+")");
        if(!query.exec()){
            QMessageBox::warning(this,"Erro","Erro ao inserir produto");
        }

        else{
            ui->txt_codigo->clear();
            ui->txt_compra->clear();
            ui->txt_descricao->clear();
            ui->txt_fornecedor->clear();
            ui->txt_venda->clear();
            ui->txt_estoque->clear();

            ui->txt_codigo->setFocus();

            QMessageBox::about(this,"sucesso","operação realizada com sucesso");
        }

 }


void fm_gestaoestoque::on_tabWidget_currentChanged(int index)
{
    if(index == 1){
        funcoes_globais::remover_linhas(ui->tw_ge_produtos);
        int contlinhas= 0;
        QSqlQuery query;
        query.prepare("select id_produtos,produto from tb_produtos order by produto");
        if(query.exec()){
            while(query.next()){
                ui->tw_ge_produtos->insertRow(contlinhas);
                ui->tw_ge_produtos->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tw_ge_produtos->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tw_ge_produtos->setRowHeight(contlinhas,20);
                contlinhas++;
            }

            ui->tw_ge_produtos->setColumnWidth(0,150);
            ui->tw_ge_produtos->setColumnWidth(1,230);

            QStringList cabecalhos = {"Codigo","Produto"};
            ui->tw_ge_produtos->setHorizontalHeaderLabels(cabecalhos);
            ui->tw_ge_produtos->setStyleSheet("QTableView{selection-background-color: red}");
            ui->tw_ge_produtos->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->tw_ge_produtos->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->tw_ge_produtos->verticalHeader()->setVisible(false);

        }

        else{
            QMessageBox::warning(this,"erro","Erro ao listar produtos");
        }
    }
}


void fm_gestaoestoque::on_tw_ge_produtos_itemSelectionChanged()
{
    int id = ui->tw_ge_produtos->item(ui->tw_ge_produtos->currentRow(),0)->text().toInt();
    QSqlQuery query;
    query.prepare("select * from tb_produtos where id_produtos ="+QString::number(id));
    if(query.exec()){
        query.first();
        ui->txt_ge_codigo->setText(query.value(0).toString());
        ui->txt_ge_produto->setText(query.value(1).toString());
        ui->txt_ge_qtd->setText(query.value(2).toString());
        ui->txt_ge_compra->setText(query.value(3).toString());
        ui->txt_ge_venda->setText(query.value(4).toString());
        ui->txt_ge_fornecedor->setText(query.value(5).toString());
    }
}

void fm_gestaoestoque::on_btn_ge_gravar_clicked()
{
    if(ui->txt_ge_codigo->text() == ""){
        QMessageBox::warning(this,"erro","Selecione um produto ");
    }
    else{
        int id = ui->tw_ge_produtos->item(ui->tw_ge_produtos->currentRow(),0)->text().toInt();
        QString aux;
        QString prod=ui->txt_ge_produto->text();
        QString forn= ui->txt_ge_fornecedor->text();
        QString qtde = ui->txt_ge_qtd->text();

        aux = ui->txt_ge_compra->text();
        std::replace(aux.begin(),aux.end(),',','.');
        QString compra = aux;

        aux = ui->txt_ge_venda->text();
        std::replace(aux.begin(),aux.end(),',','.');
        QString venda = aux;

        QSqlQuery query;
        query.prepare("update tb_produtos set id_produtos = '"+QString::number(id)+"',produto = '"+prod+"', id_fornecedor = '"+QString::number(forn.toInt())+"', qtde_estoque = '"+QString::number(qtde.toInt())+"',valor_compra = '"+QString::number(compra.toDouble())+"', valor_venda = '"+QString::number(venda.toDouble())+"' where id_produtos ="+QString::number(id));
        if(query.exec()){

            int linha= ui->tw_ge_produtos->currentRow();
            ui->tw_ge_produtos->item(linha,0)->setText(ui->txt_ge_codigo->text());
            ui->tw_ge_produtos->item(linha,1)->setText(prod);
            QMessageBox::information(this,"sucesso","produto atualizado com sucesso");
          }

          else{
                  QMessageBox::warning(this,"erro","erro ao atualizar produtos");

                }

    }
}


void fm_gestaoestoque::on_btn_ge_excluir_clicked()
{
    if(ui->txt_ge_codigo->text() == ""){
        QMessageBox::warning(this,"erro","Selecione um produto ");
    }
    else{
            QMessageBox::StandardButton opc = QMessageBox::question(this,"Exclusão","Confirma exclusão do produto?",QMessageBox::Yes|QMessageBox::No);
            if(opc==QMessageBox::Yes){
                int linha = ui->tw_ge_produtos->currentRow();
                int id = ui->tw_ge_produtos->item(linha,0)->text().toInt();
                QSqlQuery query;
                query.prepare("delete from tb_produtos where id_produtos = "+QString::number(id));
                if(query.exec()){
                    ui->tw_ge_produtos->removeRow(linha);
                    QMessageBox::information(this,"sucesso","produto deletado com sucesso");
                }

                else{
                        QMessageBox::warning(this,"erro","erro ao excluir produtos");

                      }
            }
    }
}

void fm_gestaoestoque::on_btn_ge_filtrar_clicked()
{
    QString busca;
    funcoes_globais::remover_linhas(ui->tw_ge_produtos);
    if(ui->txt_ge_filtro->text() == ""){
        if(ui->rb_ge_codigo->isChecked()){
            busca = "select id_produtos ,produto from  tb_produtos order by id_produtos";
        }

        else{
            busca = "select id_produtos ,produto from  tb_produtos order by produto";
        }
    }

    else{
        if(ui->rb_ge_codigo->isChecked()){
            busca = "select id_produtos ,produto from  tb_produtos where id_produtos = "+ui->txt_ge_filtro->text()+ "order by id_produtos";
        }

        else{
            busca = "select id_produtos ,produto from  tb_produtos where produto like '%"+ui->txt_ge_filtro->text()+"%' order by produto" ;
        }

        int contlinhas = 0;
        QSqlQuery query;
        query.prepare(busca);
        if(query.exec()){
            while(query.next()){
                ui->tw_ge_produtos->insertRow(contlinhas);
                ui->tw_ge_produtos->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tw_ge_produtos->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tw_ge_produtos->setRowHeight(contlinhas,20);
                contlinhas++;
            }


        }

        else{
            QMessageBox::warning(this,"erro","erro ao listar produotos");
        }

        ui->txt_ge_filtro->clear();
        ui->txt_ge_filtro->setFocus();
    }
}

