#ifndef FM_EDITARPRODVENDA_H
#define FM_EDITARPRODVENDA_H

#include <QDialog>

namespace Ui {
class fm_editarprodvenda;
}

class fm_editarprodvenda : public QDialog
{
    Q_OBJECT

public:
    explicit fm_editarprodvenda(QWidget *parent = nullptr);
    ~fm_editarprodvenda();

private slots:
    void on_btn_editaconfirma_clicked();

    void on_btn_editacancela_clicked();

private:
    Ui::fm_editarprodvenda *ui;
};

#endif // FM_EDITARPRODVENDA_H
