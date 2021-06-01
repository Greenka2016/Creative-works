#include "delvertform.h"
#include "ui_delvertform.h"

DelVertForm::DelVertForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelVertForm)
{
    ui->setupUi(this);
}

DelVertForm::~DelVertForm()
{
    delete ui;
}

void DelVertForm::check_max()
{
    ui->spin_vert->setMaximum(max_kol);
}

void DelVertForm::on_button_clicked()
{
    isSaved = true;
    kol = ui->spin_vert->value();
    close();
}
