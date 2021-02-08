#include "match_id.h"
#include <QPushButton>
#include "join_window.h"


match_id::match_id(join_window *my_window, std::string &id) : match_id(id)
{
    this->my_window = my_window;
}

void match_id::set_match_id()
{

}
