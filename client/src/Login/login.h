#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <atomic>

#include "../../../common/includes/Socket/SocketCommunication.h"
#include "../../../common/includes/Socket/SocketException.h"
#include "../../../common/includes/protocol.h"
#include "string.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

/**
 * @brief Qt window for the login screen. Joins or creates a match for the
 * player.
 *
 */
class Login : public QMainWindow {
  Q_OBJECT
 public:
  /**
   * @brief Construct a new Login object. Sets the styles for the buttons.
   *
   * @param host Port to connect to.
   * @param ip Ip to connect to.
   * @param game_id Match id.
   */
  Login(int& player_id, int& map_id, SocketCommunication& socket,
        std::atomic<bool>& endingGame, std::atomic<bool>& restart);
  ~Login();

 private slots:

  /**
   * @brief Parses the data and joins the given match on a join match event.
   *
   */
  void on_button_join_clicked();

  /**
   * @brief Parses the data and creates a match on a create match event.
   *
   */
  void on_button_create_clicked();

 private:
  Ui::Login* ui;
  std::string my_host;
  std::string my_ip;
  SocketCommunication& socket;
  int& player_id;
  int& map_id;
  std::atomic<bool>& endingGame;
  std::atomic<bool>& restart;
  bool connectToLobby(std::string& host, std::string& port);
  bool createLobby();
  bool joinLobby();

  std::vector<int> availableMatches;

  /**
   * @brief Receives from the given socket the ongoing match ids.
   *
   */
  bool receiveAvailableMatches();
};
#endif  // LOGIN_H
