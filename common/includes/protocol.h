#ifndef __PROTOCOL_H__
#define __PROTOCOL_H_

// Command definitions
#define CONNECT_TO_LOBBY 1
#define PLAYER_POS_UPDATE 2
#define PLAYER_SHOT_AT 3
#define PLAYER_SHOT_TO 4
#define OPEN_DOOR 5
#define PICK_WEAPON 6
#define PICK_POWERUP 7
#define PICK_KEY 8
#define PICK_TREASURE 9
#define PLAYER_DISCONNECT 10
#define PLAYER_SCORE_UPDATE 11

// Weapon ID definitions
#define KNIFE 20
#define PISTOL 21
#define MACHINEGUN 22
#define CHAINGUN 23
#define ROCKET 24

// PowerUp ID definitions
#define FOOD 30
#define MEDIKIT 31
#define BLOOD 32
#define BULLETS 33

// RESPONSE DEFINITIONS

#define CONNECTED_OK 1

#endif