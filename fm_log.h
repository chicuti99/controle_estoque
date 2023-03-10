#ifndef FM_LOG_H
#define FM_LOG_H

#include <QDialog>
#include "Conexao.h"

namespace Ui {
class fm_log;
}

class fm_log : public QDialog
{
    Q_OBJECT

public:
    explicit fm_log(QWidget *parent = nullptr);
    ~fm_log();
    bool logado;
    conection con;
    QString nome,acesso;
    int id;
    QSqlDatabase bancodedados=QSqlDatabase::addDatabase("QSQLITE");


private slots:
    void on_btn_logar_clicked();

    void on_btn_cancelar_clicked();

private:
    Ui::fm_log *ui;
};

#endif // FM_LOG_H
