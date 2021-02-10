#include "PathFactory.h"

std::string PathFactory::getTilePath(int tileId) {
  std::string path;

  switch (tileId) {
    case 124:
      path = "./elementos_mapa/items/1up.png";
      break;

    case 101:
      path = "./elementos_mapa/items/ammo.png";
      break;

    case 102:
      path = "./elementos_mapa/items/blood.png";
      break;

    case 4:
      path = "./elementos_mapa/items/chaingunitem.png";
      break;

    case 103:
      path = "./elementos_mapa/items/chest.png";
      break;

    case 107:
      path = "./elementos_mapa/items/food.png";
      break;

    case 104:
      path = "./elementos_mapa/items/goldencross.png";
      break;

    case 105:
      path = "./elementos_mapa/items/goldencrown.png";
      break;

    case 106:
      path = "./elementos_mapa/items/goldencup.png";
      break;

    case 109:
      path = "./elementos_mapa/items/medkit.png";
      break;

    case 3:
      path = "./elementos_mapa/items/machinegunitem.png";
      break;

    case 5:
      path = "./elementos_mapa/items/rocketlauncheritem.png";
      break;

    case 201:
      path = "./elementos_mapa/puertas/dark_door.png";
      break;

    case 202:
      path = "./elementos_mapa/puertas/blue_door.png";
      break;

    case 203:
      path = "./elementos_mapa/puertas/iron_door.png";
      break;

    case 108:
      path = "./elementos_mapa/puertas/goldenkey.png";
      break;

    case 110:
      path = "./elementos_mapa/decoraciones/barrel.png";
      break;

    case 111:
      path = "./elementos_mapa/decoraciones/cageskeleton.png";
      break;

    case 112:
      path = "./elementos_mapa/decoraciones/flag.png";
      break;

    case 113:
      path = "./elementos_mapa/decoraciones/floorlamp.png";
      break;

    case 114:
      path = "./elementos_mapa/decoraciones/greenbarrel.png";
      break;

    case 115:
      path = "./elementos_mapa/decoraciones/greenlight.png";
      break;

    case 116:
      path = "./elementos_mapa/decoraciones/groundskeleton.png";
      break;

    case 117:
      path = "./elementos_mapa/decoraciones/heapofbones.png";
      break;

    case 118:
      path = "./elementos_mapa/decoraciones/hungskeleton.png";
      break;

    case 119:
      path = "./elementos_mapa/decoraciones/pillar.png";
      break;

    case 120:
      path = "./elementos_mapa/decoraciones/plant.png";
      break;

    case 121:
      path = "./elementos_mapa/decoraciones/spikes.png";
      break;

    case 122:
      path = "./elementos_mapa/decoraciones/table.png";
      break;

    case 123:
      path = "./elementos_mapa/decoraciones/water.png";
      break;

    case 301:
    case 351:
      path = "./elementos_mapa/paredes/bluestone.png";
      break;

    case 303:
    case 353:
      path = "./elementos_mapa/paredes/colorstone.png";
      break;

    case 309:
    case 359:
      path = "./elementos_mapa/paredes/eagle.png";
      break;

    case 302:
    case 352:
      path = "./elementos_mapa/paredes/greystone.png";
      break;

    case 310:
    case 360:
      path = "./elementos_mapa/paredes/wall5";
      break;

    case 305:
    case 355:
      path = "./elementos_mapa/paredes/mossy.png";
      break;

    case 311:
    case 361:
      path = "./elementos_mapa/paredes/propaganda.png";
      break;

    case 308:
    case 358:
      path = "./elementos_mapa/paredes/purplestone.png";
      break;

    case 307:
    case 357:
      path = "./elementos_mapa/paredes/redbrick.png";
      break;

    case 306:
    case 356:
      path = "./elementos_mapa/paredes/skeleton.png";
      break;

    case 312:
    case 362:
      path = "./elementos_mapa/paredes/greywall.png";
      break;

    case 304:
    case 354:
      path = "./elementos_mapa/paredes/wood.png";
      break;

    case 0:
      path = "./elementos_mapa/otros/respawn_icon.png";
      break;

    default:
      break;
  }

  return path;
}
