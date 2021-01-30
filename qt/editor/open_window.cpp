#include "open_window.h"
#include "ui_open_window.h"

open_window::open_window(QWidget *parent, std::vector<std::string> maps) :
    QDialog(parent),
    ui(new Ui::open_window)
{
    ui->setupUi(this);
    this->maps_saved = maps;
}

open_window::~open_window()
{
    delete ui;
}
