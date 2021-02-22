#!/usr/bin/env bash

echo -e "\x1b[1m\x1b[32m [Installing dependencies] \x1b[0m\n"
echo -e "\x1b[1m\x1b[32m [Installing YAML-CPP] \x1b[0m\n"

cd common/src/YAML/yaml-cpp-master
mkdir build
cd build
cmake ..
sudo make install
cd ..
rm -r -f build

echo -e "\x1b[1m\x1b[32m \n [Downloading Lua] \x1b[0m\n"
curl -R -O http://www.lua.org/ftp/lua-5.4.2.tar.gz
tar zxf lua-5.4.2.tar.gz
cd lua-5.4.2
make linux
sudo make install
cd ..
rm lua-5.4.2

echo -e "\x1b[1m\x1b[32m \n [Compiling Server] \x1b[0m\n"
cd ../../../../
cmake .
make
sudo mv ServerMain /usr/local/bin

echo -e "\x1b[1m\x1b[32m \n [Compiling Editor] \x1b[0m\n"
cd qt/editor/
cmake .
make
cd ../../

echo -e "\x1b[1m\x1b[32m \n [Compiling Client] \x1b[0m\n"
cd client/executable
cmake .
make
sudo mv Wolfen3D /usr/local/bin
cd ..
sudo cp -r Wolfenstein /usr/local/share

echo -e "\x1b[1m\x1b[32m \n [Install finished] \x1b[0m\n"
