#include "fm_log.h"
#include "ui_fm_log.h"
#include <QMessageBox>
#include <QDebug>

fm_log::fm_log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_log)
{
    ui->setupUi(this);

}

fm_log::~fm_log()
{
    delete ui;
}

void fm_log::on_btn_logar_clicked()
{

    QSqlQuery query;
    if(!con.abrir()) {
        QMessageBox::warning(this,"erro","erro ao abrir db");
         qDebug() << query.lastError().text();
    }

    else{
         QString username,senha;
         username =ui->txt_username->text();
         senha = ui->txt_senha->text();


         if(!query.exec("select * from controlEstoque where username_colab = '"+username+" ' and senha_colab = '"+senha+"'")){
             qDebug() << query.lastError().text();
         }
    }

    //con.fecha();
}

