# Taller de Programación I - Cátedra Veiga - FIUBA
# Trabajo Práctico Final

| Padrón | Alumno                    |
|--------|---------------------------|
| 104105 | Jonathan David Rosenblatt |
| 103924 | Joaquín Fontela           |
| 104348 | Joaquin Betz Rivera       |
| 104429 | Thiago Kovnat             |

# Guia de Instalación
## Requisitos
Ademas de las librerias que utiliza el juego, el unico otro requisito que necesita el trabajo es contar con una computadora que utilice GNU/Linux como sistema operativo.

## Instalación de dependencias

Dependiendo del gestor de paquetes, el comando para instalar las dependencias puede variar. Sin embargo, los paquetes a instalar son siempre los mismos. A continuación, se deja los comandos para instalar SDL 2.0 y Qt5 para el correcto funcionamiento del trabajo práctico utilizando el gestor de paquetes APT utilizado en muchas distribuciones de Linux.

```
sudo apt-get install libsdl2-dev &&
sudo apt-get install libsdl2-image-dev -y &&
sudo apt-get install libsdl2-mixer-dev -y &&
sudo apt-get install libsdl2-ttf-dev -y &&
sudo apt-get install qt5-default &&
```
## Configuración, compilación e instalacion de librerias YAML
Una vez instaladas las dependencias previas, se debe de utilizar el script install.sh brindado en el repositorio para la instalación de la libreria de parsing de YAML y para compilar el trabajo. Dicho script se puede correr utilizando el siguiente comando. Cabe recalcar que se necesitan de derechos de administrador dado que la instalacion de la libreria YAML lo requiere.

```
chmod +x install.sh
./install.sh
```

## Forma de Uso
### Servidor
Dentro de la carpeta principal del repositorio, se encontrara el ejecutable del servidor, al cual se lo debe llamar utilizando el siguiente comando
```
./ServerMain <PORT> <configFilePath>
```
Siendo PORT el puerto a utlizar y configFilePath el path al archivo de configuracion que utiliza el juego para balancear las constantes numericas.

### Cliente
Para correr el cliente, se debe entrar a la carpeta client/executable. Desde la carpeta principal del repositorio basta con hacer cd client/executable para posicionarse dentro de la misma. Para correr el ejecutable, debe de usarse el siguiente comando

```
./Wolfen3D
```
Siendo HOST la direccion del servidor a utilizar, y siendo PORT el puerto en el que el servidor este aceptando clientes.

## Apéndice de Errores

El sistema puede tener glitches que causen, o no, diferentes tipos de interferencias en la experiencia del usuario. Para notificar esto y para generar un registro de potenciales problemas que aparecen se usa un log de errores.

El mismo, en caso de que se necesite, escribe en el archivo _"wolfenstein.log"_ (ubicado en el mismo directorio donde se encuentra el ejecutable del cliente) la información correspondiente.

Llamando a la macro `LOG(std::string errorMsg)` se llama al método estático de la clase `Log` que recibe el archivo, la función, la línea y `errorMsg` para escribirlos en el log con el formato antes escrito.

### Clasificación de Errores

Los potenciales mensajes de errores que pueden aparecer son:

- `"Error, track not found with code: [CODE NUMBER]"`: Ocurre en el `audiomanager.cpp` cuando no se encuentra el track con el código dado. Para saber que track es el que falla se puede abrir el `clientprotocol.h` en el cliente y buscar el que nombre de archivo con el código dado causa el problema.   

- `"Error, texture already found with code: [CODE NUMBER]"`: Ocurre en el `audiomanager.cpp` al inicializar los audio tracks. Ocurre si se lee el mismo archivo dos veces. Para saber que track es el que falla se puede abrir el `clientprotocol.h` en el cliente y buscar el que nombre de archivo con el código dado causa el problema.   

- `"Error, no missile texture to explode found."`: Si se reporta este error, signfica que no se pudieron encontrar las coordenadas del último frame del misil en el aire. Glitch no fatal.

- `"Error, no hostname and/or port given."`: Error de Lua que ocurre cuando no se pasan los argumentos correspondientes al ejecutable.

- `"Error, cannot add more textures with code: "`: Ocurre cuando se intenta añadir una cantidad de texturas mayor al límite recomendado. Es un error no fatal que puede ser ignorado o arreglado modificando el límite de texturas en `clientprotocol.h` (cambiar la macro `TEXTURE_LIMIT`).

- `"Error, texture not found with code: "`: Ocurre en el `texturemanager.cpp` cuando no se encuentra la imagen con el código dado. Para saber que imagen es el que falla se puede abrir el `clientprotocol.h` en el cliente y buscar el que nombre de archivo con el código dado causa el problema.   

- `"Error, texture already found with code: [CODE NUMBER]"`:  Ocurre en el `texturemanager.cpp` al inicializar las SdlTextures. Ocurre si se lee la misma imagen dos veces. Para saber que archivo es el que falla se puede abrir el `clientprotocol.h` en el cliente y buscar el que nombre de archivo con el código dado causa el problema.   

- `"Error, map not found: [FILE NAME]"`: Sube este error si no se encuentra el .yaml del mapa correspondiente.

- `"Fatal error, the player couldn't be created."`: Surge si la máquina no puede, por la razon que sea, crear dinámicamente una instancia del jugador. Si es ocasionado por una falta de recursos se debería cerrar cualquier proceso que de forma innecesaria coma recursos.

- `"Fatal error, the executer couldn't be created."`: Surge si la máquina no puede, por la razon que sea, crear dinámicamente una instancia del CommandExecuter (responsable de recibir información del server). Si es ocasionado por una falta de recursos se debería cerrar cualquier proceso que de forma innecesaria coma recursos.

- `"Fatal error, the sender couldn't be created."`: Surge si la máquina no puede, por la razon que sea, crear dinámicamente una instancia del CommandSender (responsable de mandar información del server). Si es ocasionado por una falta de recursos se debería cerrar cualquier proceso que de forma innecesaria coma recursos.

- `"Error, can't push a null pointer as a sprite."`: Ocurre si se intenta guardar un sprite nulo. Puede ser la consecuencia de no tener los recursos para crear estas instancias; en tal caso se debería cerrar cualquier proceso que de forma innecesaria tome recursos.

- Cualquier otro tipo de error loggeado es el el resultado de llamar al método `what()` de la excepción que haya finalizado la vida del programa y es fatal.
