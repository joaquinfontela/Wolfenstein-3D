function DownloadMaps(){
  svn export https://github.com/joaquinfontela/Taller-95.08-TP_Final/trunk/common/src/YAML/Maps
  sudo mv Maps/* /usr/local/share/Wolfenstein/YAML/Maps
  rm -r Maps
}

function moveMaps(){
  sudo cp qt/editor/maps/*.yaml /usr/local/share/Wolfenstein/YAML/Maps
}

case $1 in
-a)
  DownloadMaps
  moveMaps
  ;;
-d)
  DownloadMaps
  ;;
-m)
  moveMaps
  ;;
-h)
  echo -e "Help:
  -a -> Download official maps and move user-created maps to media folder
  -d -> Only download official maps
  -m -> Only moves user-created maps to media folder"
  ;;
esac
