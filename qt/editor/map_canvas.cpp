#include "map_canvas.h"
#include <vector>
#include "tile.h"
#include <QMessageBox>
#include <iostream>

map_canvas::map_canvas(int col,int row)
{
    this->grilla = {};
    for(int i = 0; i < row ; i++){
        std::vector<std::vector<tile*>> new_row;
        for(int x = 0; x < col; x++){
            std::vector<tile*> col_vector;
            new_row.push_back(col_vector);
        }
        grilla.push_back(new_row);
    }
    this->cant_col = col;
    this->cant_row = row;
}

bool map_canvas::paint_tile(std::vector<int> coordinates, tile* new_tile){
    int row = coordinates[0]-1;
    int col = coordinates[1]-1;
    std::vector<tile*> vector_selected = this->grilla.at(row).at(col);
    if(vector_selected.empty() || (vector_selected[0]->accept_tile(new_tile) && vector_selected.size() < 4)){
        this->grilla.at(row).at(col).push_back(new_tile);
        return true;
    }else if(!new_tile->cumulative || !(vector_selected[0]->cumulative)){
        this->grilla.at(row).at(col).clear();
        this->grilla.at(row).at(col).push_back(new_tile);
        return true;
    }
    QMessageBox messageBox;
    messageBox.critical(0,"Error","No puedes agregar este elemento aqui!");
    messageBox.setFixedSize(500,200);
    messageBox.exec();
    return false;
}

std::vector<tile*> map_canvas::tiles_at_coordinates(std::vector<int> coordinates){
    return this->grilla.at(coordinates[0]-1).at(coordinates[1]-1);
}











