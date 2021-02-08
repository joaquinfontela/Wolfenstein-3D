#include "save_window.h"
#include "ui_save_window.h"
#include "../../common/includes/YAML/YAMLConfigReader.h"
#include "../../common/includes/YAML/YAMLMapReader.h"
#include "../../common/includes/YAML/YAMLMapWriter.h"
#include "QPushButton"
#include "QMessageBox"
#include "editor.h"
#include <fstream>

#define MAP_NAME_PATH "./maps/maps_names.txt"

typedef std::vector<std::vector<std::vector<tile_item*>>> TileMatrix;

save_window::save_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::save_window)
{
    ui->setupUi(this);
    this->editor = (Editor*)parent;
}

save_window::~save_window()
{
    delete ui;
}

void save_window::on_pushButton_clicked()
{
    QString name = ui->name_value->text();
    if(name.isEmpty()){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","No has escrito el nombre!!");
        messageBox.setFixedSize(500,200);
        messageBox.exec();
    }else{
        std::string name_str = name.toStdString();

        std::string name_path = "./maps/" +  name_str + ".yaml";
        YAMLMapWriter* map_creator = new YAMLMapWriter(name_path);
        TileMatrix matrix = this->editor->mc->grilla;
        map_creator->createYamlMapFile(matrix);
        delete map_creator;

        this->editor->actual_map_name = name_str;
        std::ofstream writer(MAP_NAME_PATH, std::ios::out | std::ios::app);
        writer << name_str << std::endl;
        writer.close();
        this->close();
   }
}
