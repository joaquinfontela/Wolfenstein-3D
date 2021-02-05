#include "login.h"

#include "QMessageBox"
#include "QString"
#include "iostream"
#include "ui_login.h"

Login::Login(QWidget *parent) : QMainWindow(parent), ui(new Ui::Login) {
  ui->setupUi(this);
}

Login::~Login() { delete ui; }

void Login::on_boton_continuar_clicked() {
  QString ip = ui->dato_ip->text();
  QString nombre = ui->dato_nombre->text();
  QString puerto = ui->dato_puerto->text();
  if (puerto.isEmpty() || nombre.isEmpty() || ip.isEmpty()) {
    QMessageBox messageBox;
    messageBox.critical(0, "Error", "Faltan datos!!!");
    messageBox.setFixedSize(800, 600);
    messageBox.exec();
  } else {
    std::string ip_str = ip.toStdString();
    std::string nombre_str = nombre.toStdString();
    std::string puerto_str = puerto.toStdString();
    std::cout << "tu nombre es :" << nombre_str << std::endl;
    std::cout << "tu ip es :" << ip_str << std::endl;
    std::cout << "tu puerto es :" << puerto_str << std::endl;
    QApplication::quit();
  }
}
