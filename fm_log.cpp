#include "fm_log.h"
#include "ui_fm_log.h"
#include <QMessageBox>
#include <QDebug>
#include <QVariant>
#include "fm_principal.h"
#include "variaveis_globais.h"

//static QSqlDatabase bancodedados=QSqlDatabase::addDatabase("QSQLITE");

fm_log::fm_log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_log)
{
    ui->setupUi(this);
    logado = false;

}

fm_log::~fm_log()
{
    delete ui;
}

void fm_log::on_btn_logar_clicked()
{

    QSqlQuery query;


    //QString local= qApp->applicationDirPath();
    //QString banco = local+"banco_de_dados0.db";
    bancodedados.setDatabaseName("C:/Users/Usuario/Documents/estudos/c++/QTcreator/controle_estoque/db.db");

    if(!bancodedados.open()) {
        qDebug() << query.lastError().text();
        QMessageBox::warning(this,"erro","db nao abriu");
    }

    else{
         QString username,senha;
         username =ui->txt_username->text();
         senha = ui->txt_senha->text();
         if(query.exec("SELECT * FROM colaboradores WHERE username='"+username+"' AND senha='"+senha+"'")){
             query.first();
             if(query.value(1).toString() !=""){
                 variaveis_globais::logado = true;
                 variaveis_globais::nome_colab=query.value(1).toString();
                variaveis_globais::id_colab = query.value(0).toInt();
                 variaveis_globais::acesso_colab=query.value(5).toString();
                 QMessageBox::information(this,"Sucesso","login realizado");
                 bancodedados.close();
                 close();
             }
             else{
                  QMessageBox::warning(this,"erro","colaborador não encontrado");
             }
         }

         else{
              qDebug() << query.lastError().text();
              QMessageBox::warning(this,"erro","Erro na consulta");
         }
         bancodedados.close();
    }


}


void fm_log::on_btn_cancelar_clicked()
{
    logado = false;
    close();
}

/*bool fm_log::getlogado()
{
    return logado;

}

QString fm_log::getnome()
{
    return nome;
}


QString fm_log::getacesso()
{
    return acesso;
}*/
