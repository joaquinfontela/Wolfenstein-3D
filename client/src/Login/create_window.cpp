#include "create_window.h"

#include <QMessageBox>

#include "iostream"
#include "ui_create_window.h"

create_window::create_window(QWidget *parent)
    : QDialog(parent), ui(new Ui::create_window) {
  ui->setupUi(this);
}

create_window::~create_window() { delete ui; }

uint32_t create_window::get_map_id() { return (uint32_t)my_map_id; }

void create_window::on_pushButton_clicked() {
  QString new_map_id = ui->map_id_line->text();
  if (new_map_id.isEmpty()) {
    QMessageBox messageBox;
    messageBox.critical(0, "Error", "Map id missing!");
    messageBox.setFixedSize(500, 200);
    messageBox.exec();
  } else {
    my_map_id = new_map_id.toInt();
    this->close();
  }
}
