#include "fm_gestaocolaboradores.h"
#include "ui_fm_gestaocolaboradores.h"
#include <QtSql>
#include <QMessageBox>
#include "funcoes_globais.h"
static QSqlDatabase bancodedados=QSqlDatabase::addDatabase("QSQLITE");

fm_gestaocolaboradores::fm_gestaocolaboradores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_gestaocolaboradores)
{
    ui->setupUi(this);
    QSqlDatabase bancodedados=QSqlDatabase::addDatabase("QSQLITE");
    bancodedados.setDatabaseName("C:/Users/Usuario/Documents/estudos/c++/QTcreator/controle_estoque/db.db");
    if(!bancodedados.open()) {
         QMessageBox::about(this,"erro","Erro ao abrir banco de dados");
     }

    ui->cb_novapermissao->addItem("A");
    ui->cb_novapermissao->addItem("B");
    ui->cb_age_acesso->addItem("A");
    ui->cb_age_acesso->addItem("A");
    ui->txt_novocolab->setFocus();

       ui->tw_ge_listacolab->setColumnCount(2);
       ui->tabWidget->setCurrentIndex(0);

       ui->tw_ge_listacolab->setColumnWidth(0,100);
       ui->tw_ge_listacolab->setColumnWidth(1,50);

       QStringList cabecalhos = {"ID","Nome"};
       ui->tw_ge_listacolab->setHorizontalHeaderLabels(cabecalhos);
       ui->tw_ge_listacolab->setStyleSheet("QTableView{selection-background-color: red}");
       ui->tw_ge_listacolab->setEditTriggers(QAbstractItemView::NoEditTriggers);
       ui->tw_ge_listacolab->setSelectionBehavior(QAbstractItemView::SelectRows);
       ui->tw_ge_listacolab->verticalHeader()->setVisible(false);

}

fm_gestaocolaboradores::~fm_gestaocolaboradores()
{
    delete ui;
}

void fm_gestaocolaboradores::on_btn_novocolab_clicked()
{
    ui->txt_novasenha->clear();
    ui->txt_novocolab->clear();
    ui->txt_novotelefone->clear();
    ui->txt_novousername->clear();

    ui->cb_novapermissao->setCurrentIndex(0);
    ui->txt_novocolab->setFocus();
}


void fm_gestaocolaboradores::on_btn_gravarnovocolab_clicked()
{

    QString nome = ui->txt_novocolab->text();
    QString username = ui->txt_novousername->text();
    QString senha = ui->txt_novasenha->text();
    QString telefone = ui->txt_novotelefone->text();
    QString acesso = ui->cb_novapermissao->currentText();




     QSqlQuery query;
     query.prepare("insert into colaboradores (nome,username,senha,telefone,acesso) values "
                   "('"+nome+"','"+username+"','"+senha+"','"+telefone+"','"+acesso+"')");
     if(!query.exec()){
         qDebug()<<query.lastError().text();
         QMessageBox::critical(this,"Erro","Erro ao inserir colaborador");
     }

     else{
         QMessageBox::information(this,"Erro","colaborador gravado com sucesso");
         ui->txt_novocolab->clear();
         ui->txt_novousername->clear();
         ui->txt_novasenha->clear();
         ui->txt_novotelefone->clear();
         ui->cb_novapermissao->setCurrentIndex(0);

         ui->txt_novocolab->setFocus();

         QMessageBox::about(this,"sucesso","operação realizada com sucesso");
     }
}


void fm_gestaocolaboradores::on_btn_cancelarnovo_clicked()
{

}


void fm_gestaocolaboradores::on_tabWidget_currentChanged(int index)
{
    if(index == 1){
        funcoes_globais::remover_linhas(ui->tw_ge_listacolab);
        int contlinhas= 0;
        QSqlQuery query;
        query.prepare("select id,nome from colaboradores order by id");
        if(query.exec()){
            while(query.next()){
                ui->tw_ge_listacolab->insertRow(contlinhas);
                ui->tw_ge_listacolab->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tw_ge_listacolab->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tw_ge_listacolab->setRowHeight(contlinhas,20);
                contlinhas++;
            }

        }

        else{
            qDebug() <<query.lastError().text();
            QMessageBox::warning(this,"erro","Erro ao listar colaboradores");
        }
    }
}


void fm_gestaocolaboradores::on_tw_ge_listacolab_itemSelectionChanged()
{
    int idi = ui->tw_ge_listacolab->item(ui->tw_ge_listacolab->currentRow(),0)->text().toInt();
    QSqlQuery query;
    query.prepare("select * from colaboradores where id ="+QString::number(idi));
    if(query.exec()){
        query.first();
        ui->txt_nome_gecolab->setText(query.value(1).toString());
        ui->username_gecolab->setText(query.value(2).toString());
        ui->txt_senha_gecolab->setText(query.value(3).toString());
        ui->tel_gecolab->setText(query.value(4).toString());
        ui->cb_age_acesso->setCurrentText(query.value(5).toString());
    }
}


void fm_gestaocolaboradores::on_btn_ge_filtrar_clicked()
{
    QString busca;
    funcoes_globais::remover_linhas(ui->tw_ge_listacolab);
    if(ui->filtro_gecolab->text() == ""){
        if(ui->rb_ge_id->isChecked()){
            busca = "select id,nome from  colaboradores order by id";
        }

        else{
            busca = "select id,nome from  colaboradores order by nome";
        }
    }

    else{
        if(ui->rb_ge_id->isChecked()){
            busca = "select id,nome from  colaboradores where id = '"+ui->filtro_gecolab->text()+"'order by id";
        }

        else{
            busca = "select id,nome from  colaboradores where nome like '%"+ui->filtro_gecolab->text()+"%' order by nome" ;
        }

        int contlinhas = 0;
        QSqlQuery query;
        query.prepare(busca);
        if(query.exec()){
            while(query.next()){
                ui->tw_ge_listacolab->insertRow(contlinhas);
                ui->tw_ge_listacolab->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
                ui->tw_ge_listacolab->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
                ui->tw_ge_listacolab->setRowHeight(contlinhas,20);
                contlinhas++;
            }


        }

        else{
            qDebug()<<query.lastError().text();
            QMessageBox::warning(this,"erro","erro ao listar colaboradores");
        }

        ui->filtro_gecolab->clear();
        ui->filtro_gecolab->setFocus();
    }
}


void fm_gestaocolaboradores::on_btn_ge_salvar_clicked()
{
    if(ui->tw_ge_listacolab->currentRow() == -1){
        QMessageBox::warning(this,"erro","selecione um item");
        return;
    }

    QString id = ui->tw_ge_listacolab->item(ui->tw_ge_listacolab->currentRow(),0)->text();

    QSqlQuery query;
    QString nome = ui->txt_nome_gecolab->text();
    QString usernamee = ui->username_gecolab->text();
    QString senha = ui->txt_senha_gecolab->text();
    QString tel = ui->tel_gecolab->text();
    QString acesso = ui->cb_age_acesso->currentText();
    query.prepare("update colaboradores set nome = '"+nome+"',username = '"+usernamee+"', senha = '"+senha+"', telefone = '"+tel+"',acesso = '"+acesso+"' where id ="+ id);
    if(query.exec()){

        int linha= ui->tw_ge_listacolab->currentRow();
        ui->tw_ge_listacolab->item(linha,1)->setText(nome);
        QMessageBox::information(this,"sucesso","colaborador atualizado com sucesso");
      }

      else{
              QMessageBox::warning(this,"erro","erro ao atualizar produtos");

            }
}


void fm_gestaocolaboradores::on_btn_ge_excluir_clicked()
{
    if(ui->tw_ge_listacolab->currentRow() == -1){
        QMessageBox::warning(this,"erro","selecione um item");
        return;
    }

    QMessageBox::StandardButton opc = QMessageBox::question(this,"Exclusão","Confirma exclusão do colaborador?",QMessageBox::Yes|QMessageBox::No);
    if(opc==QMessageBox::Yes){
        int linha = ui->tw_ge_listacolab->currentRow();
        QString id = ui->tw_ge_listacolab->item(linha,0)->text();
        QSqlQuery query;
        query.prepare("delete from colaboradores where id = "+id);
        if(query.exec()){
            ui->tw_ge_listacolab->removeRow(linha);
            QMessageBox::information(this,"sucesso","colaborador deletado com sucesso");
        }

        else{
                QMessageBox::warning(this,"erro","erro ao excluir colaborador");

              }
    }
}

