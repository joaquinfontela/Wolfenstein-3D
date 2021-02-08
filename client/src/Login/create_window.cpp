#include "create_window.h"
#include "ui_create_window.h"
#include <QMessageBox>

create_window::create_window(QWidget *parent, int& map_id) :
    QDialog(parent),
    ui(new Ui::create_window),
    my_map_id(map_id)
{
    ui->setupUi(this);
}

create_window::~create_window()
{
    delete ui;
}

void create_window::on_pushButton_clicked()
{
    QString map_id = ui->map_id_line->text();
    if(map_id.isEmpty()){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","match id missing!");
        messageBox.setFixedSize(500,200);
        messageBox.exec();
    }else{
         my_map_id = map_id.toInt();
         this->close();
    }
}
