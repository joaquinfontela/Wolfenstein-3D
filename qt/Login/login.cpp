#include "login.h"

#include <QPixmap>

#include "../../client/includes/client.h"
#include "QFont"
#include "QFontDatabase"
#include "QMessageBox"
#include "QString"
#include "iostream"
#include "string.h"
#include "ui_login.h"

Login::Login(std::string& host, std::string& ip, int& game_id)
    : QMainWindow(nullptr),
      ui(new Ui::Login),
      my_host(host),
      my_ip(ip),
      my_game_id(game_id) {
  ui->setupUi(this);
  QPixmap bkgnd("./loginscreen.png");
  bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
  QPalette palette;
  palette.setBrush(QPalette::Background, bkgnd);
  this->setPalette(palette);
  ui->dato_puerto->setPlaceholderText(" PORT");
  ui->dato_game->setPlaceholderText(" MATCH ID");
  ui->dato_ip->setPlaceholderText(" IP");
}

Login::~Login() { delete ui; }

void Login::on_button_join_clicked() {
  QString ip = ui->dato_ip->text();
  QString game_id = ui->dato_game->text();
  QString puerto = ui->dato_puerto->text();
  if (puerto.isEmpty() || game_id.isEmpty() || ip.isEmpty()) {
    QMessageBox messageBox;
    messageBox.critical(0, "Error", "Faltan datos!!!");
    messageBox.setFixedSize(800, 600);
    messageBox.exec();
  } else {
    my_ip = ip.toStdString();
    my_game_id = game_id.toInt();
    my_host = puerto.toStdString();

    QApplication::quit();
  }
}

void Login::on_button_create_clicked() {}
