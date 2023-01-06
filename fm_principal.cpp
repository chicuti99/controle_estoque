#include "fm_principal.h"
#include "ui_fm_principal.h"
#include <QMessageBox>
#include "fm_log.h"
#include "fm_nova_venda.h"
#include "fm_gestaocolaboradores.h"
#include "fm_gestaoestoque.h"
#include "fm_gestaovendas.h"

int fm_principal::id_colab;
QString fm_principal::acesso_colab;
QString fm_principal::nome_colab;
QString fm_principal::username_colab;
bool fm_principal::logado;

fm_principal::fm_principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::fm_principal)
{
    ui->setupUi(this);
    logado = false;
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
    if(!logado){
           fm_log f_logar;
           f_logar.exec();


           if(logado){
               ui->btn_bloquear->setIcon(*cadaberto);
               ui->lb_nome->setText(nome_colab);
           }
    }

    else{
        logado = true;
        ui->btn_bloquear->setIcon(*cadaberto);
         ui->lb_nome->setText("sem colaborador");

    }
}


void fm_principal::on_pushButton_3_clicked()
{
    if(logado){
        fm_nova_venda f_novavenda;
        f_novavenda.exec();
    }

    else{
        QMessageBox::about(this,"erro","Não existe colaborador logado");
    }
}


void fm_principal::on_actionEstoque_triggered()
{
    if(logado && acesso_colab== "A"){
        fm_gestaoestoque f_gestaoestoque;
        f_gestaoestoque.exec();
  }

    else{
        QMessageBox::about(this,"erro","ACESSO NEGADO");
    }
}


void fm_principal::on_actionColaboradores_triggered()
{
    if(logado && acesso_colab== "A"){
        fm_gestaocolaboradores f_gestacolab;
        f_gestacolab.exec();
  }

    else{
        QMessageBox::about(this,"erro","ACESSO NEGADO");
    }
}


void fm_principal::on_actionVendas_triggered()
{
    if(logado && acesso_colab== "A"){
        fm_gestaovendas f_gestaovenda;
        f_gestaovenda.exec();
  }

    else{
        QMessageBox::about(this,"erro","ACESSO NEGADO");
    }
}

