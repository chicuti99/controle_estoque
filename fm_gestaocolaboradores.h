#ifndef FM_GESTAOCOLABORADORES_H
#define FM_GESTAOCOLABORADORES_H

#include <QDialog>

namespace Ui {
class fm_gestaocolaboradores;
}

class fm_gestaocolaboradores : public QDialog
{
    Q_OBJECT

public:
    explicit fm_gestaocolaboradores(QWidget *parent = nullptr);
    ~fm_gestaocolaboradores();

private:
    Ui::fm_gestaocolaboradores *ui;
};

#endif // FM_GESTAOCOLABORADORES_H
