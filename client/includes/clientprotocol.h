#ifndef CLIENTPROTOCOL_H_
#define CLIENTPROTOCOL_H_
#include "log.h"

#define LOG_WITH_ID(Y) LOG((Y + std::to_string(id)).c_str())
#define LOG(ERROR) Log::log(__FILE__, __FUNCTION__, __LINE__, ERROR);

#define ERROR -1
#define HEIGHT 600
#define WIDTH 800

#define TIME_PER_ANIMATION_SLIDE 200.0

#define BLOOD_FRAMES 5

// Apply bit masks to facilitate the sound selection.

#define TIMES_THE_AUDIO_IS_PLAYED 1
#define IS_MUSIC true
#define MUSIC_VOLUME 7
#define DOOR_VOLUME 20
#define SHOOTING_VOLUME 7

#define GET_WEAPON_SOUND(X) X

/* AUDIO CODES */

#define KNIFE_SOUND 1
#define PISTOL_SOUND 2
#define MACHINEGUN_SOUND 3
#define CHAINGUN_SOUND 4
#define ROCKETLAUNCHER_SOUND 5
#define EXPLOSION_SOUND 6
#define DOOR_SOUND 7
#define PICKUP_SOUND 8
#define HEALTH_PICKUP_SOUND 9
#define DOG_DEATH_SOUND 10
#define SOLDIER_DEATH_SOUND 11
#define SS_DEATH_SOUND 12
#define OFFICIAL_DEATH_SOUND 13
#define MUTANT_DEATH_SOUND 14
#define MUSIC 15
#define SECRET_DOOR_SOUND 16

#define GET_DEATH_SOUND(X) (X+DOG_DEATH_SOUND-1)
#define IS_GUN_SOUND(X) (X >= KNIFE_SOUND && X <= ROCKETLAUNCHER_SOUND)

#define KNIFE 1
#define PISTOL 2
#define MACHINEGUN 3
#define CHAINGUN 4
#define ROCKETLAUNCHER 5

#define AUDIO_PATH "/usr/local/share/Wolfenstein/audio/"
#define FONT_PATH "/usr/local/share/Wolfenstein/media/"
#define IMG_PATH "/usr/local/share/Wolfenstein/media/"
#define GAME_FONT "wolfenstein.ttf"
#define GAME_LOGO "wolfensteinlogo.jpg"
#define GAME_TITLE "Wolfenstein"

#define TEXTURE_LIMIT 200
#define GREY 169, 168, 244
#define CEILING_COLOR 0x7B, 0x7B, 0x7B
#define FLOOR_COLOR 0x60, 0x60, 0x60
#define OTHER_COLOR 0xFF, 0xFF, 0x60

#define PI 3.14159265359
#define BLOCKSIZE 64

/* SPRITE CODES */

#define BLUEWALL 1
#define WALL2_SPRITE 2
#define GUARD_SPRITE 3
#define CHAINGUN_SPRITE 4
#define HUD_SPRITE 5
#define GREENLIGHT_SPRITE 6
#define SMALLBARREL_SPRITE 7
#define SOLDIER_FRONT_OLD 8
#define SOLDIERRIGHT_SPRITE 9
#define SOLDIERBACK_SPRITE 10
#define SOLDIERLEFT_SPRITE 11
#define WALL5_SPRITE 12
#define BJ1_SPRITE 13
#define BJ2_SPRITE 14
#define BJ3_SPRITE 15
#define BJ4_SPRITE 16
#define BJ5_SPRITE 17
#define BJ6_SPRITE 18
#define BJ7_SPRITE 19
#define HUDGUNS 20
#define GUNSPRITESROW 21
#define GREY_STONE_WALL 22
#define WOODEN_WALL 23
#define DOOR 24
#define ONEUP 25
#define AMMO 26
#define ARMOR 27
#define BASKET 28
#define BED 29
#define BLOOD 30
#define BLOODYSKELETON 31
#define BLUEKEY 32
#define CAGE 33
#define CAGESKELETON 34
#define CHAINGUNITEM 35
#define CHAIRANDTABLE 36
#define CHANDELIER 37
#define DOGFOOD 38
#define EMPTYWELL 39
#define FLAG 40
#define FLOORLAMP 41
#define FLOWERPOT 42
#define FOOD 43
#define CHEST 44
#define GOLDENCROSS 45
#define GOLDENCROWN 46
#define GOLDENCUP 47
#define GOLDENKEY 48
#define GREENBARREL 49
#define GROUNDSKELETON 50
#define HEAPOFBONES 51
#define HUNGSKELETON 52
#define LAMP 53
#define MACHINEGUNITEM 54
#define MEDKIT 55
#define PILLAR 56
#define PLANT 57
#define POT 58
#define SINK 59
#define SPIKES 60
#define STOVE 61
#define TABLE 62
#define UTENSILHOLDER 63
#define UTENSILS 64
#define VEINS 65
#define WATER 66
#define WELL 67
#define MOSSY 68
#define BRICKWALL 69
#define PURPLEWALL 70
#define HUDKEY 71
#define ROCKETLAUNCHERITEM 72
#define FLYINGMISSILE 73
#define EXPLOSION 74
#define DAMAGE_HUD 75

#define DOG_DEATH 76
#define SOLDIER_DEATH 77
#define SS_DEATH 78
#define OFFICIAL_DEATH 79
#define MUTANT_DEATH 80

#define DOG_FRONT 81
#define SOLDIER_FRONT 82
#define SS_FRONT 83
#define OFFICIAL_FRONT 84
#define MUTANT_FRONT 85

#define DOG_SPRINT 86
#define SOLDIER_SPRINT 87
#define SS_SPRINT 88
#define OFFICER_SPRINT 89
#define MUTANT_SPRINT 90
#define DOG_ATTACK 91
#define SOLDIER_ATTACK 92
#define SS_ATTACK 93
#define OFFICER_ATTACK 94
#define MUTANT_ATTACK 95
#define LOCKED_DOOR 96
#define HIGHSCORE 97
#define COLORSTONE 98
#define WALL_3 99
#define EAGLE_WALL 100
#define STARTING_SCREEN 101

#define GET_STANDING_IMG_FROM_GUNID(X) (X + DOG_FRONT - 1)
#define GET_MOVING_ANIMATION_FROM_GUNID(X) (DOG_SPRINT - 1 + X)
#define GET_SHOOTING_ANIMATION_FROM_GUNID(X) (DOG_ATTACK - 1 + X)
#define GET_DEATH_ANIMATION_SPRITE(X) (X + DOG_DEATH - 1)
#define GET_GUN_ID_FROM_ANIMATION_SPRITE(X) (X - (DOG_DEATH - 1))
#define IS_HEALTH_UP(ID) (ID == BLOOD || ID == MEDKIT || ID == FOOD)
#define GET_BJ_FACE_FROM_HEALTH(HP) (BJ1_SPRITE + 7 - ceil(float(HP * 7)/100.0))

#define FRAMES_PER_DEATH_ANIMATION 5
#define FRAMES_PER_EXPLOSION_ANIMATION 3

#define CLOSED 'c'
#define CLOSING 'C'
#define OPEN 'o'
#define OPENING 'O'
#define DOOR_ANIMATION_TIME 1.0

#define COULD_NOT_CREATE_PLAYER "Fatal error, the player couldn't be created."

#endif  // CLIENTPROTOCOL_H_
