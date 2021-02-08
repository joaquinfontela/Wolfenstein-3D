#include "join_window.h"
#include "ui_join_window.h"
#include <QVBoxLayout>
#include "match_id.h"
#include <QMessageBox>

join_window::join_window(QWidget *parent, uint32_t &lobbyID, std::vector<int> availableMatches) :
    QDialog(parent),
    ui(new Ui::join_window),
    match_id(lobbyID)
    {
    ui->setupUi(this);
    QVBoxLayout* ly = new QVBoxLayout();
    ly->setSpacing(10);

    for(size_t i = 0; i < availableMatches.size(); i++){
        match_id* mid = new class match_id(this, availableMatches.at(i));
        ly->addWidget(mid,0,Qt::AlignTop);
     }
    ui->id_container->setLayout(ly);
}

join_window::~join_window()
{
    delete ui;
}

void join_window::on_join_button_clicked()
{
    if(this->match_id == -1){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","No has seleccionado un mapa!!");
        messageBox.setFixedSize(500,200);
        messageBox.exec();
    }else{
        this->close();
    }
}
