#include "create_window.h"
#include "ui_create_window.h"

create_window::create_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::create_window)
{
    ui->setupUi(this);
}

create_window::~create_window()
{
    delete ui;
}
