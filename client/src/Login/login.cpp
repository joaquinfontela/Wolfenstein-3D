#include "login.h"

#include <QPixmap>
#include <algorithm>

#include "./Login_autogen/include/ui_login.h"
#include "QFont"
#include "QFontDatabase"
#include "QMessageBox"
#include "QString"
#include "iostream"
#include "string.h"

#define BLACK_BUTTON_OR_BOX \
  "* { background-color: rgba(0, 0, 0, 200); color: #ffffff}"
#define WHITESPACE ' '

Login::Login(int& player_id, int& map_id, SocketCommunication& socket)
    : QMainWindow(nullptr),
      ui(new Ui::Login),
      player_id(player_id),
      map_id(map_id),
      socket(socket)
      {
  ui->setupUi(this);
  QPixmap bkgnd("../media/loginscreen.png");
  bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
  QPalette palette;
  palette.setBrush(QPalette::Background, bkgnd);
  this->setPalette(palette);
  ui->dato_puerto->setPlaceholderText(" PORT");
  ui->dato_game->setPlaceholderText(" MATCH ID");
  ui->dato_ip->setPlaceholderText(" IP");
  ui->dato_puerto->setStyleSheet(BLACK_BUTTON_OR_BOX);
  ui->dato_game->setStyleSheet(BLACK_BUTTON_OR_BOX);
  ui->dato_ip->setStyleSheet(BLACK_BUTTON_OR_BOX);
  ui->button_join->setStyleSheet(BLACK_BUTTON_OR_BOX);
  ui->button_create->setStyleSheet(BLACK_BUTTON_OR_BOX);
}

Login::~Login() { delete ui; }

void Login::on_button_join_clicked() {
  QString ip = ui->dato_ip->text();
  QString game_id = ui->dato_game->text();
  QString port = ui->dato_puerto->text();
  auto parseSpaces = [](const std::string& s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    std::string ans = (end == std::string::npos) ? "" : s.substr(0, end + 1);
    size_t start = ans.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : ans.substr(start);
  };
  if (port.isEmpty() || game_id.isEmpty() || ip.isEmpty()) {
    QMessageBox messageBox;
    messageBox.critical(0, "Error", "Complete all the boxes.");
    messageBox.setFixedSize(800, 600);
    messageBox.exec();
  } else {
    my_ip = parseSpaces(ip.toStdString());
    my_host = parseSpaces(port.toStdString());
   // my_game_id = game_id.toInt();


    // PARTE DE CONECTARSE A UNA PARTIDA

    this->socket.connect(my_ip, my_host);

    uint32_t protocol = JOIN_LOBBY;
    uint32_t opcode;
    uint32_t selfID;
    uint32_t mapID;

    // Connection Request
    socket.send(&protocol, sizeof(protocol));

    receiveAvailableMatches(); //recibo las partidas disponibles
    uint32_t lobbyID = -1;
    
    
    // QT

     
    socket.send(&lobbyID, sizeof(lobbyID));
    // Connection Response
    socket.receive(&opcode, sizeof(opcode));

    if (opcode != CONNECTED_OK){
      this->player_id = -1;
      QApplication::quit();
      return;
    }
      
    socket.receive(&selfID, sizeof(selfID));
    socket.receive(&mapID, sizeof(mapID));
    
    this->player_id = selfID;
    this->map_id = mapID;

    QApplication::quit();
  }
}

void Login::on_button_create_clicked() {
  /*QString ip = ui->dato_ip->text();
  QString game_id = ui->dato_game->text();
  QString port = ui->dato_puerto->text();
  auto parseSpaces = [](const std::string& s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    std::string ans = (end == std::string::npos) ? "" : s.substr(0, end + 1);
    size_t start = ans.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : ans.substr(start);
  };
  if (port.isEmpty() || game_id.isEmpty() || ip.isEmpty()) {
    QMessageBox messageBox;
    messageBox.critical(0, "Error", "Complete all the boxes.");
    messageBox.setFixedSize(800, 600);
    messageBox.exec();
  } else {
    my_ip = parseSpaces(ip.toStdString());
    my_host = parseSpaces(port.toStdString());
    my_game_id = game_id.toInt();
    QApplication::quit();
  }*/
}

void Login::receiveAvailableMatches(){

  uint32_t amountOfMatches = 0;
  this->socket.receive(&amountOfMatches, sizeof(amountOfMatches));

  for(uint32_t i = 0; i < amountOfMatches; i++){

    uint32_t matchID;
    this->socket.receive(&matchID, sizeof(matchID));
    this->availableMatches.push_back(matchID);
  }
}

bool Login::joinLobby(){

  uint32_t protocol = JOIN_LOBBY;
  uint32_t opcode;
  uint32_t selfID;

  // Connection Request
  socket.send(&protocol, sizeof(protocol));

  receiveAvailableMatches();
  

  // Connection Response
  socket.receive(&opcode, sizeof(opcode));

  if (opcode != CONNECTED_OK) return false;

  socket.receive(&selfID, sizeof(selfID));
  this->player_id = selfID;
  

  return true;


}
