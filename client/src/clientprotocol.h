#ifndef CLIENTPROTOCOL_H_
#define CLIENTPROTOCOL_H_

#define HEIGHT 600
#define WIDTH 800

// Apply bit masks to facilitate the sound selection.

#define TIMES_THE_AUDIO_IS_PLAYED 1

#define GET_WEAPON_SOUND(X) X

#define KNIFE_SOUND 1
#define PISTOL_SOUND 2
#define MACHINEGUN_SOUND 3
#define CHAINGUN_SOUND 4
#define ROCKETLAUNCHER_SOUND 5

#define KNIFE 1
#define PISTOL 2
#define MACHINEGUN 3
#define CHAINGUN 4
#define ROCKETLAUNCHER 5

#define AUDIO_PATH "../audio/"
#define FONT_PATH "../media/"
#define IMG_PATH "../media/"
#define GAME_FONT "wolfenstein.ttf"
#define GAME_LOGO "wolfensteinlogo.jpg"
#define GAME_TITLE "Wolfenstein"

#define TEXTURE_LIMIT 64
#define GREY 169, 168, 244
#define CEILING_COLOR 0x7B, 0x7B, 0x7B
#define FLOOR_COLOR 0x60, 0x60, 0x60
#define OTHER_COLOR 0xFF, 0xFF, 0x60

#define PI 3.14159265359
#define BLOCKSIZE 64
#define FPS_FREQ 500

#define BLUE_WALL 1
#define WALL2_SPRITE 2
#define GUARD_SPRITE 3
#define CHAINGUN_SPRITE 4
#define HUD_SPRITE 5
#define GREENLIGHT_SPRITE 6
#define SMALLBARREL_SPRITE 7
#define SOLDIERFRONT_SPRITE 8
#define SOLDIERRIGHT_SPRITE 9
#define SOLDIERBACK_SPRITE 10
#define SOLDIERLEFT_SPRITE 11
#define HITLERWALL_SPRITE 12
#define BJ1_SPRITE 13
#define BJ2_SPRITE 14
#define BJ3_SPRITE 15
#define HUDGUNS 16
#define GUNSPRITESROW 17
#define GREY_STONE_WALL 18
#define ROCK_WALL 19
#define WOODEN_WALL 20


#endif  // CLIENTPROTOCOL_H_
