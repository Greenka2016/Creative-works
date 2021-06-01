#ifndef DELVERTFORM_H
#define DELVERTFORM_H

#include <QDialog>

namespace Ui {
class DelVertForm;
}

class DelVertForm : public QDialog
{
    Q_OBJECT

public:
    explicit DelVertForm(QWidget *parent = nullptr);
    ~DelVertForm();

    int max_kol;
    int kol;
    bool isSaved = false;

    void check_max();

private slots:
    void on_button_clicked();

private:
    Ui::DelVertForm *ui;
};

#endif // DELVERTFORM_H
