#include "newmatrixform.h"
#include "ui_newmatrixform.h"

NewMatrixForm::NewMatrixForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMatrixForm)
{
    ui->setupUi(this);
}

NewMatrixForm::~NewMatrixForm()
{
    delete ui;
}

void NewMatrixForm::on_button_clicked()
{
    verts = ui->spinVerts->value();
    edges = ui->spinEdges->value();
    isSaved = true;
    close();
}
