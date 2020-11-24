Variables:

```
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int W;
    int H;

    +---------------------------------------------------------------+
    |                                                               |
    |    +-----------------------------------------------------+    |
    |    |                                                     |    |  Siendo SCREEN_HEIGHT y SCREEN_WIDTH el
    |    |                                                     |    | tamaño de toda la pantalla. W y H son el 
    |    |                        W * H ---------------------->|    | las dimensiones del espacio jugable.
    |    |                        |                            |    |  W < SCREEN_WIDTH & H < SCREEN_HEIGHT ya
    |    |                        |                            |    | que una parte de la pantalla la ocupa el 
    |    |                        v                            |    | HUD.
    |    +-----------------------------------------------------+    |
    |                                                               |
    |                                                               |
    |                                                               | <-----+
    +---------------------------------------------------------------+       |
                                                ^                           |   
                                                |                           |
                                                +------ SCREEN_WIDTH* SCREEN_HEIGHT

    Map<int,Textura> textures;
    int[n][m] map;
    List<Jugadores> players; // Imporante para saber las (x,y) de cada player, entre otros datos importantes.
    SDL_Window window;
```

Código del render:

<br><p align="center"><img src="media/mapcalcs.PNG"/></p> 

```
  for _ in 0,30: // Que genere las imágenes 30 veces por segundo.
    for i in 0,W: // Por cada columna de píxeles en el espacio de juego (sección de pantalla sin el HUD).
      (n0,m0) = findMyCellOnTheMap(map,x,y)
      // Siendo n0 y m0 las coordenadas de la matriz en la que se encuentra mi personaje.
      
      alpha = calcVisionAngle(x,y,KeyboardEvent); // O MouseEvent si se usa el mouse...

      int cx,cy; // Las coordenadas donde colisiona el rayo.
      if (pi/2 > alpha) and (alpha > 0): // Rayo mirando para adelante.
        cx = floor(x/64) * 64 - 1;
      else: // Rayo mirando para atrás.
        cx = floor(x/64) * 64 + 64;

      // Hasta acá, (cx,cy) son las coordenadas de la primera intersección entre el rayo de visión y 
      // una celda de la matriz.
      
      while (true): // En este ciclo voy a buscar intersecciones con paredes.
```
