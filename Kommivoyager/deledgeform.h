#ifndef DELEDGEFORM_H
#define DELEDGEFORM_H

#include <QDialog>

namespace Ui {
class DelEdgeForm;
}

class DelEdgeForm : public QDialog
{
    Q_OBJECT

public:
    explicit DelEdgeForm(QWidget *parent = nullptr);
    ~DelEdgeForm();
    int max_kol;
    int source, target;
    bool isSaved;

    void check_max();

private slots:
    void on_button_clicked();

private:
    Ui::DelEdgeForm *ui;
};

#endif // DELEDGEFORM_H
