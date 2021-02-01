#include "size_window.h"
#include "ui_size_window.h"
#include <QMessageBox>

#define SIDE_SIZE 40

size_window::size_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::size_window)
{
    ui->setupUi(this);
    this->editor = (Editor*)parent;
}

size_window::~size_window()
{
    delete ui;
}

void size_window::on_pushButton_clicked()
{
    QString anchura_str = ui->dato_anchura->text();
    int tiles_anchura = anchura_str.toInt();
    QString altura_str = ui->dato_altura->text();
    int tiles_altura = altura_str.toInt();
    if(tiles_altura < 15 || tiles_anchura < 15){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","El minimo tamaño es de 15x15!");
        messageBox.setFixedSize(500,200);
        messageBox.exec();
    }else{
         this->editor->initialize_map_container(tiles_anchura, tiles_altura);
         this->close();
    }
}
