svn export https://github.com/joaquinfontela/tp-final-taller/trunk/common/src/YAML/Maps
sudo mv Maps/* qt/editor/maps
rm -r Maps
sudo cp qt/editor/maps/*.yaml /usr/local/share/Wolfenstein/YAML/Maps
