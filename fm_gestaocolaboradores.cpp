#include "fm_gestaocolaboradores.h"
#include "ui_fm_gestaocolaboradores.h"

fm_gestaocolaboradores::fm_gestaocolaboradores(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_gestaocolaboradores)
{
    ui->setupUi(this);
}

fm_gestaocolaboradores::~fm_gestaocolaboradores()
{
    delete ui;
}
