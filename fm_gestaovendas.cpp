#include "fm_gestaovendas.h"
#include "ui_fm_gestaovendas.h"
#include "fm_gestaoestoque.h"
#include "ui_fm_gestaoestoque.h"
#include <QtSql>
#include <QMessageBox>
#include "funcoes_globais.h"
#include <QPrinter>
#include <QPainter>
#include <QDir>
#include <QPixmap>
#include <QDesktopServices>
static QSqlDatabase bancodedados=QSqlDatabase::addDatabase("QSQLITE");


fm_gestaovendas::fm_gestaovendas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fm_gestaovendas)
{
    ui->setupUi(this);
    QSqlDatabase bancodedados=QSqlDatabase::addDatabase("QSQLITE");
        bancodedados.setDatabaseName("C:/Users/Usuario/Documents/estudos/c++/QTcreator/controle_estoque/db.db");
       if(!bancodedados.open()) {
            QMessageBox::about(this,"erro","Erro ao abrir banco de dados");
        }

       QSqlQuery query;
       query.prepare("select * from tb_vendas ");
       query.exec();
       query.first();
       ui->tw_listavenda->horizontalHeader()->setVisible(true);
       ui->tw_listavenda->setColumnCount(6);
       QStringList cabe = {"id","data","hora","colab","V.total","Tipo pgto"};
        ui->tw_listavenda->setHorizontalHeaderLabels(cabe);
        ui->tw_listavenda->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tw_listavenda->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tw_listavenda->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tw_listavenda->setEditTriggers(QAbstractItemView::NoEditTriggers);


        ui->tw_listavendas->horizontalHeader()->setVisible(true);
        ui->tw_listavendas->setColumnCount(5);
        QStringList cabe1 = {"mov","produto","Qtde","Valor U.","V.total"};
         ui->tw_listavendas->setHorizontalHeaderLabels(cabe1);
         ui->tw_listavendas->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
         ui->tw_listavendas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
         ui->tw_listavendas->setSelectionBehavior(QAbstractItemView::SelectRows);
         ui->tw_listavendas->setEditTriggers(QAbstractItemView::NoEditTriggers);

        int contlinhas = 0;
       do{
           ui->tw_listavendas->insertRow(contlinhas);
           ui->tw_listavendas->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
           ui->tw_listavendas->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
           ui->tw_listavendas->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
           ui->tw_listavendas->setItem(contlinhas,3,new QTableWidgetItem(query.value(3).toString()));
           ui->tw_listavendas->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
           ui->tw_listavendas->setItem(contlinhas,5,new QTableWidgetItem(query.value(5).toString()));

       }while(query.next());
}

fm_gestaovendas::~fm_gestaovendas()
{
    delete ui;
}

void fm_gestaovendas::on_tw_listavenda_itemSelectionChanged()
{
    ui->tw_listavenda->setRowCount(0);
    QSqlQuery query;
    query.prepare("select id_movimentacao,produto,qtde,valor_un,valor_total from tb_vendidos where id_venda ="+ui->tw_listavendas->item(ui->tw_listavenda->currentRow(),0)->text());
    query.exec();
    query.first();

    int contlinhas = 0;
   do{
       ui->tw_listavenda->insertRow(contlinhas);
       ui->tw_listavenda->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
       ui->tw_listavenda->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
       ui->tw_listavenda->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
       ui->tw_listavenda->setItem(contlinhas,3,new QTableWidgetItem(query.value(3).toString()));
       ui->tw_listavenda->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
   }while(query.next());

}


void fm_gestaovendas::on_btn_filtrar_clicked()
{
    int contlinhas = 0;
    QSqlQuery query;
    query.prepare("select * from tb_vendas where data_venda between '"+ui->de_inicial->text()+"'and'"+ui->de_final->text()+"'" );
    query.exec();
    query.first();

    do{
        ui->tw_listavenda->insertRow(contlinhas);
        ui->tw_listavenda->setItem(contlinhas,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tw_listavenda->setItem(contlinhas,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tw_listavenda->setItem(contlinhas,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tw_listavenda->setItem(contlinhas,3,new QTableWidgetItem(query.value(3).toString()));
        ui->tw_listavenda->setItem(contlinhas,4,new QTableWidgetItem(query.value(4).toString()));
    }while(query.next());
}


void fm_gestaovendas::on_pushButton_2_clicked()
{
    QString nome = ui->tw_listavendas->item(ui->tw_listavendas->currentRow(),0)->text()+"_vendas.pdf";
    QString local = QDir::currentPath()+"/"+ui->tw_listavendas->item(ui->tw_listavendas->currentRow(),0)->text()+"_vendas.pdf";
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(nome);

    QPainter painter;
    if(!painter.begin(&printer)){
        qDebug() <<"erro ao abrir pdf";
        return;
    }

    int linha = 300,salto =20 ;

    painter.drawPixmap(25,25,QPixmap(":/teste/unlocked.png"));


    painter.drawText(23,200,"ID:"+ui->tw_listavendas->item(ui->tw_listavendas->currentRow(),0)->text());

    painter.drawText(150,200,"Data:"+ui->tw_listavendas->item(ui->tw_listavendas->currentRow(),1)->text());

    printer.newPage();
    for (int i = 0;i<ui->tw_listavenda->rowCount();i++){
        painter.drawText(23,linha,ui->tw_listavenda->item(i,0)->text());
        painter.drawText(50,linha,ui->tw_listavenda->item(i,1)->text());
        painter.drawText(300,linha,ui->tw_listavenda->item(i,2)->text());
        linha += salto;
    }
    painter.drawText(25,25,"arthur ");
    painter.end();

QDesktopServices::openUrl(QUrl("file:///"+nome));
}

