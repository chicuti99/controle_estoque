#ifndef FM_PRINCIPAL_H
#define FM_PRINCIPAL_H

#include <QMainWindow>
#include<QtSql>
QT_BEGIN_NAMESPACE
namespace Ui { class fm_principal; }
QT_END_NAMESPACE

class fm_principal : public QMainWindow
{
    Q_OBJECT

public:
    fm_principal(QWidget *parent = nullptr);
    ~fm_principal();
    QIcon cadfechado;
    QIcon *cadaberto= new QIcon();



private slots:
    void on_btn_bloquear_clicked();

    void on_pushButton_3_clicked();

    void on_actionEstoque_triggered();

    void on_actionColaboradores_triggered();

    void on_actionVendas_triggered();

private:
    Ui::fm_principal *ui;
};
#endif // FM_PRINCIPAL_H
