#!/usr/bin/env bash

echo -e "Installing dependencies...\n"
echo -e "Installing YAML-CPP: \n"

cd common/src/YAML/yaml-cpp-master
mkdir build
cd build
cmake ..
sudo make install
cd ..
rm -r -f build

echo -e "\n Compiling Server...\n"
cd ../../../../
cmake .
make

echo -e "\n Compiling Client...\n"
cd client/executable
cmake .
make


echo -e "\n Install finished. \n"
