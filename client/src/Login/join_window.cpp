#include "join_window.h"

#include <QMessageBox>
#include <QVBoxLayout>

#include "match_id.h"
#include "ui_join_window.h"

join_window::join_window(QWidget* parent, std::vector<int> availableMatches)
    : QDialog(parent), ui(new Ui::join_window) {
  ui->setupUi(this);
  QVBoxLayout* ly = new QVBoxLayout();
  ly->setSpacing(10);
  bool is_first_iteration = true;
  match_id* last_mi;
  for (size_t i = 0; i < availableMatches.size(); i++) {
    match_id* new_match_id = new class match_id(this, availableMatches.at(i));
    if(is_first_iteration){
        QObject::connect(ly, &QObject::destroyed, new_match_id, &QObject::deleteLater);
        last_mi = new_match_id;
        is_first_iteration = false;
     }else{
        QObject::connect(last_mi, &QObject::destroyed, new_match_id, &QObject::deleteLater);
        last_mi = new_match_id;
     }
     ly->addWidget(new_match_id, 0, Qt::AlignTop);
  }
  ui->id_container->setLayout(ly);
  my_match_id = -1;
}

join_window::~join_window() {
    delete ui->id_container->layout();
    delete ui;
}

uint32_t join_window::get_match_id() { return (uint32_t)this->my_match_id; }

void join_window::on_join_button_clicked() {
  if (this->my_match_id == -1) {
    QMessageBox messageBox;
    messageBox.critical(0, "Error", "No has seleccionado un mapa!!");
    messageBox.setFixedSize(500, 200);
    messageBox.exec();
  } else {
    this->close();
  }
}
