#include "map_save.h"
#include "QPushButton"
#include "open_window.h"
#include "tile.h"
#include "iostream"
#include "../../common/includes/YAML/YAMLConfigReader.h"
#include "../../common/includes/YAML/YAMLMapReader.h"
#include "../../common/includes/YAML/YAMLMapWriter.h"
#include "YAMLConversor.h"

map_save::map_save(open_window* my_window, std::string map_name)
{
    this->my_window = my_window;
    connect (this, SIGNAL(clicked()), this, SLOT(set_map()));
    this->setMaximumWidth(450);
    this->setMinimumHeight(40);
    QFont f( "Yrsa semibold", 25);
    this->setText(QString::fromStdString(map_name));
    this->setFont(f);
    std::string file_path = "./maps/" + map_name + ".YAML";
    YAMLConversor* conversor = new YAMLConversor(file_path);
    this->map = *conversor->updateTileMatrix();
}

void map_save::set_map(){
    my_window->map_selected = &this->map;
}

