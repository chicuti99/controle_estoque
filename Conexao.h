#ifndef CONEXAO_H
#define CONEXAO_H
#include <QtSql>
#include <QDialog>
#include <QMessageBox>

class conection{
public:
    QSqlDatabase bancodedados;
    conexao(){
        bancodedados=QSqlDatabase::addDatabase("QSQLITE");
    }

    void fecha(){
        bancodedados.close();
    }

    bool abrir(){
        QString local= qApp->applicationDirPath();
        QString banco = local+"banco_de_dados.db";
        bancodedados.setDatabaseName(banco);
        bancodedados.open();

        if(!bancodedados.open()){
            return false;
            //QMessageBox::warning(this,"Falha","ERRO na classe");
        }

        else {
            return true;
        }
    }
};

#endif // CONEXAO_H
