#include "fm_principal.h"
#include "ui_fm_principal.h"
#include <QMessageBox>
#include "fm_log.h"


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




}

fm_principal::~fm_principal()
{
    delete ui;
}


void fm_principal::on_btn_bloquear_clicked()
{
    if(!logado ){
           fm_log f_logar;
           f_logar.exec();
    }

    else{
        logado = true;
        ui->btn_bloquear->setIcon(*cadaberto);

    }
}

