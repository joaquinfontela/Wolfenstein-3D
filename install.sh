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

echo -e "\x1b[1m\x1b[32m \n [Compiling Server] \x1b[0m\n"
cd ../../../../
cmake .
make

echo -e "\x1b[1m\x1b[32m \n [Compiling Client] \x1b[0m\n"
cd client/executable
cmake .
make


echo -e "\x1b[1m\x1b[32m \n [Install finished] \x1b[0m\n"
