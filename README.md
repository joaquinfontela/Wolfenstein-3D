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
## Compilación e instalacion de librerias YAML
Una vez instaladas las dependencias previas, se debe de utilizar el script install.sh brindado en el repositorio para la instalación de la libreria de parsing de YAML y para compilar el trabajo. Dicho script se puede correr utilizando el siguiente comando. Cabe recalcar que se necesitan de derechos de administrador dado que la instalacion de la libreria YAML lo requiere.

```
chmod +x install.sh
./install.sh
```

## Ejecutar el trabajo
### Servidor
Dentro de la carpeta principal del repositorio, se encontrara el ejecutable del servidor, al cual se lo debe llamar utilizando el siguiente comando
```
./ServerMain <PORT> <configFilePath>
```
Siendo PORT el puerto a utlizar y configFilePath el path al archivo de configuracion que utiliza el juego para balancear las constantes numericas.

### Cliente
Para correr el cliente, se debe entrar a la carpeta client/executable. Desde la carpeta principal del repositorio basta con hacer cd client/executable para posicionarse dentro de la misma. Para correr el ejecutable, debe de usarse el siguiente comando

```
./Wolfen3D <HOST> <PORT>
```
Siendo HOST la direccion del servidor a utilizar, y siendo PORT el puerto en el que el servidor este aceptando clientes.
