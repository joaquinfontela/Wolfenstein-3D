#include "mousetileactions.h"
#include "QEvent"
#include "QCursor"
#include "tile.h"
#include <iostream>
#include <QMouseEvent>

mouseTileActions::mouseTileActions(Editor* editor){
    this->editor = editor;
}

bool mouseTileActions::eventFilter(QObject *obj, QEvent *event){
        if (event->type() == QEvent::MouseButtonPress) {
           QMouseEvent* me = (QMouseEvent*)event;
           int x = me->localPos().x();
           int y = me->localPos().y();
           if(this->editor->tile_container != NULL){
               tile* tile_clicked = this->editor->tile_container->tile_clicked(x, y);
               if(tile_clicked != NULL){
                   this->editor->tile_selected = tile_clicked;
               }
           }
           return true;
        } else{
            return QObject::eventFilter(obj, event);
        }
}



