#include "fm_gestaovendas.h"
#include "ui_fm_gestaovendas.h"

fm_gestaovendas::fm_gestaovendas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_gestaovendas)
{
    ui->setupUi(this);
}

fm_gestaovendas::~fm_gestaovendas()
{
    delete ui;
}
