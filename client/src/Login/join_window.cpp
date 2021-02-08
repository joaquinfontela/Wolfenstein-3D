#include "join_window.h"
#include "ui_join_window.h"

join_window::join_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::join_window)
{
    ui->setupUi(this);
}

join_window::~join_window()
{
    delete ui;
}
