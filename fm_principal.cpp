#include "fm_principal.h"
#include "ui_fm_principal.h"
#include <QMessageBox>
#include "fm_log.h"
#include "fm_nova_venda.h"
#include "fm_gestaocolaboradores.h"
#include "fm_gestaoestoque.h"
#include "fm_gestaovendas.h"
#include "variaveis_globais.h"

int variaveis_globais::id_colab;
QString variaveis_globais::acesso_colab;
QString variaveis_globais::nome_colab;
QString variaveis_globais::username_colab;
bool variaveis_globais::logado;

fm_principal::fm_principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::fm_principal)
{
    ui->setupUi(this);
    variaveis_globais::logado = false;
    cadfechado.addFile(":/teste/lock.png");
    cadaberto->addFile(":/teste/unlocked.png");

    ui->btn_bloquear->setIcon(cadfechado);
    ui->statusbar->addWidget(ui->btn_bloquear);
     ui->statusbar->addWidget(ui->lb_nome);




}

fm_principal::~fm_principal()
{
    delete ui;
}


void fm_principal::on_btn_bloquear_clicked()
{
    if(!variaveis_globais::logado){
           fm_log f_logar;
           f_logar.exec();


           if(variaveis_globais::logado){
               ui->btn_bloquear->setIcon(*cadaberto);
               ui->lb_nome->setText(variaveis_globais::nome_colab);
           }
    }

    else{
        variaveis_globais::logado = true;
        ui->btn_bloquear->setIcon(*cadaberto);
         ui->lb_nome->setText("sem colaborador");

    }
}


void fm_principal::on_pushButton_3_clicked()
{
    if(variaveis_globais::logado){
        fm_nova_venda f_novavenda;
        f_novavenda.exec();
    }

    else{
        QMessageBox::about(this,"erro","Não existe colaborador logado");
    }
}


void fm_principal::on_actionEstoque_triggered()
{
    if(variaveis_globais::logado && variaveis_globais::acesso_colab== "A"){
        fm_gestaoestoque f_gestaoestoque;
        f_gestaoestoque.exec();
  }

    else{
        QMessageBox::about(this,"erro","ACESSO NEGADO");
    }
}


void fm_principal::on_actionColaboradores_triggered()
{
    if(variaveis_globais::logado && variaveis_globais::acesso_colab== "A"){
        fm_gestaocolaboradores f_gestacolab;
        f_gestacolab.exec();
  }

    else{
        QMessageBox::about(this,"erro","ACESSO NEGADO");
    }
}


void fm_principal::on_actionVendas_triggered()
{
    if(variaveis_globais::logado && variaveis_globais::acesso_colab== "A"){
        fm_gestaovendas f_gestaovenda;
        f_gestaovenda.exec();
  }

    else{
        QMessageBox::about(this,"erro","ACESSO NEGADO");
    }
}

