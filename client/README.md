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
                                                +------ SCREEN_WIDTH * SCREEN_HEIGHT

    Map<int,Textura> textures;
    int[n][m] map; // Cada bloque de la matriz será un cuadrado de pxp píxeles.
    List<Jugadores> players; // Imporante para saber las (x,y) de cada player, entre otros datos importantes.
    SDL_Window window;
```

Código del cálculo de las coordenadas de la intersección del rayo con la pared.:

<br><p align="center"><img src="media/mapcalcs.PNG"/></p> 

```
  for _ in 0,30:  // Que genere las imágenes 30 veces por segundo.
    for i in 0,W: // Por cada columna de píxeles en el espacio de juego (sección de pantalla sin el HUD).
      (n0,m0) = findMyCellOnTheMap(map,x,y); // Siendo n0 y m0 las coordenadas de la matriz en 
                                             // la que se encuentra mi personaje.
      
      alpha = calcVisionAngle(x,y,KeyboardEvent); // O MouseEvent si se usa el mouse...

      int cx,cy; // Las coordenadas donde colisiona el rayo.
      if (pi/2 > alpha) and (alpha > 0): // Rayo mirando para adelante.
        cy = floor(x/p) * p - 1;
      else: // Rayo mirando para atrás.
        cy = floor(x/p) * p + p;
      cx = x + (y - cy)/tan(alpha)

      // Hasta acá, (cx,cy) son las coordenadas de la primera intersección 
      // entre el rayo de visión y una celda de la matriz.
      
      deltay = (pi/2 > alpha) and (alpha > 0) ? p : -p;
      deltax = abs(deltay)/tan(alpha);

      while (true): // En este ciclo voy a buscar intersecciones con paredes.
        if (isAWall(map[cx][cy])):
          break;
        cy += deltay; // Salgo del loop con las coordenadas de la intersección.
        cx += deltax;

      int distanceToWall = abs(x - cx)/cos(alpha) + abs(y - cy)/sin(alpha);
      distanceToWall *= cos(pi/2 - alpha); // Ajustando el "fishbowl effect"

      int p' = (p * W) / (distanceToWall * 2 * tan(pi/2 - FOV));
      // p' representa la altura de la pared a renderizar en la columna de la actual iteración.

```

Con p' ya podemos calcular dibujar la tira de 1xp' píxeles que representa un cachito de textura.