#ifndef NEWEDGEFORM_H
#define NEWEDGEFORM_H

#include <QDialog>

namespace Ui {
class NewEdgeForm;
}

class NewEdgeForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewEdgeForm(QWidget *parent = nullptr);
    ~NewEdgeForm();
    int max_kol;
    int source, target, weight;
    bool isSaved = false;
    void check_max();

private slots:
    void on_button_clicked();

private:
    Ui::NewEdgeForm *ui;
};

#endif // NEWEDGEFORM_H
