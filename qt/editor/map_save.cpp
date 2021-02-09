#include "map_save.h"
#include "QPushButton"
#include "open_window.h"
#include "iostream"
#include "../../common/includes/YAML/YAMLConfigReader.h"
#include "../../common/includes/YAML/YAMLMapReader.h"
#include "../../common/includes/YAML/YAMLMapWriter.h"
#include "YAMLConversor.h"

map_save::map_save(open_window* my_window, std::string map_name_)
{
    this->my_window = my_window;
    connect (this, SIGNAL(clicked()), this, SLOT(set_map()));
    this->setMaximumWidth(450);
    this->setMinimumHeight(40);
    QFont f( "Yrsa semibold", 25);
    this->setText(QString::fromStdString(map_name_));
    this->setFont(f);
    std::string file_path = "./maps/" + map_name_ + ".yaml";
    YAMLConversor* conversor = new YAMLConversor(file_path);
    this->map = conversor->updateTileMatrix();
    this->map_name = map_name_;
    delete conversor;
}

map_save::~map_save()
{
    if(this->my_window->map_name != this->map_name){
        int cant_col = this->map->at(0).size();
        int cant_row = this->map->size();
        for (int i = 0; i < cant_row; i++) {
            for (int x = 0; x < cant_col; x++) {
                int row = i;
                int col = x;
                size_t size = this->map->at(row).at(col).size();
                for(size_t y = 0; y < size; y++){
                    delete this->map->at(row).at(col).at(y);
                }
            }
        }
    }
    delete this->map;
}

void map_save::set_map(){
    my_window->map_selected = this->map;
    my_window->map_name = this->map_name;
}

