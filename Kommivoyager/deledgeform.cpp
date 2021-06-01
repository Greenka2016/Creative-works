#include "deledgeform.h"
#include "ui_deledgeform.h"

DelEdgeForm::DelEdgeForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelEdgeForm)
{
    ui->setupUi(this);
}

DelEdgeForm::~DelEdgeForm()
{
    delete ui;
}

void DelEdgeForm::check_max()
{
    ui->spin_source->setMaximum(max_kol);
    ui->spin_target->setMaximum(max_kol);
}
void DelEdgeForm::on_button_clicked()
{
    isSaved = true;
    source = ui->spin_source->value();
    target = ui->spin_target->value();
    close();
}
