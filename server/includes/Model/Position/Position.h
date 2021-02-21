#ifndef __POSITION_H__
#define __POSITION_H__


#include "../Map/Map.h"
#include "../../../../common/includes/Queue/WaitingQueue.h"
#include "../../Control/Notification/Notification.h"
#include "../../../../common/includes/PlayerData.h"


/*
 * @section DESCRIPTION
 * Class that represents a position on the map
 */

class Map;
class Player;


class Position{

private:

    double x, y;
    double dirX, dirY;
    double moveSpeed, rotSpeed;
    double planeX, planeY;
    Player* player;

public:
    explicit Position(Player* player, Map& map);

    /*
     * @brief Fills the PlayerData struct with the correct info.
     *
     * @param PlayerData struct to fill
     */
    void fillData(PlayerData& data);

    /*
     * @brief Respawn onto a new location
     *
     * @param Map on which to respawn
     */
    void respawn(Map& map, WaitingQueue<Notification*>& notis);

    /*
     * @brief Updates the current position of the player.
     *
     * @param Map on which to move.
     * @param Time elapsed since last update.
     * @param Notification Queue on which to notify of changes.
     *
     * @return True if movement occured, false otherwise.
     */
    bool update(Map& map, float timeElapsed, WaitingQueue<Notification*>& notis);

    /*
     * @brief Updates the movement speed
     *
     * @param Movement speed to add
     */
    void updateMoveSpeed(double moveSpeed);

    /*
     * @brief Updates the rotation speed
     *
     * @param Rotation speed to add
     */
    void updateRotationSpeed(double rotSpeed);


    /*
    * @brief [SERVER-SIDE] Checks collision with a coordinate (x, y)
    *
    * @param X Coordinate
    * @param Y Coordinate
    *
    * @return True if the collision occured, false otherwise.
    */
    bool collidesWith(double x, double y);

    //GETTERS
    double getX();
    double getY();
    double getDirX();
    double getDirY();
    double getPlaneX();
    double getPlaneY();

};

#endif
