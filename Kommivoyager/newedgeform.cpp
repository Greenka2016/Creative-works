#include "newedgeform.h"
#include "ui_newedgeform.h"

NewEdgeForm::NewEdgeForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewEdgeForm)
{
    ui->setupUi(this);
}

NewEdgeForm::~NewEdgeForm()
{
    delete ui;
}

void NewEdgeForm::check_max()
{
    ui->spin_source->setMaximum(max_kol);
    ui->spin_target->setMaximum(max_kol);
}
void NewEdgeForm::on_button_clicked()
{
    isSaved = true;
    source = ui->spin_source->value();
    target = ui->spin_target->value();
    weight = ui->spin_weight->value();
    close();
}
