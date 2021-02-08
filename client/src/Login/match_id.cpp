#include "match_id.h"
#include <QPushButton>
#include "join_window.h"


match_id::match_id(join_window *my_window, int id) : match_id(id)
{
    this->my_window = my_window;
    connect (this, SIGNAL(clicked()), this, SLOT(set_match_id()));
    this->setMaximumWidth(300);
    this->setMinimumHeight(30);
    QFont f( "Yrsa semibold", 25);
    this->setText(QString::fromStdString(std::to_string(match_id)));
    this->setFont(f);
}

void match_id::set_match_id()
{
    my_window->match_id = this->match_id;
}
