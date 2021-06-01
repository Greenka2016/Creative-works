#ifndef NEWMATRIXFORM_H
#define NEWMATRIXFORM_H

#include <QDialog>

namespace Ui {
class NewMatrixForm;
}

class NewMatrixForm : public QDialog
{
    Q_OBJECT

public:
    explicit NewMatrixForm(QWidget *parent = nullptr);
    ~NewMatrixForm();

    int verts, edges;
    bool isSaved = false;

private slots:
    void on_button_clicked();

private:
    Ui::NewMatrixForm *ui;
};

#endif // NEWMATRIXFORM_H
