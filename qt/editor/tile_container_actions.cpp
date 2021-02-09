#include "tile_container_actions.h"
#include <QEvent>
#include <QMouseEvent>
#include "tiles_container.h"
#include "QApplication"
#include "ui_editor.h"

tile_container_actions::tile_container_actions(Editor* editor){
    this->editor = editor;
}


bool tile_container_actions::eventFilter(QObject *obj, QEvent *event){
        if (event->type() == QEvent::MouseButtonPress) {
           QMouseEvent* me = (QMouseEvent*)event;
           int x = me->localPos().x();
           int y = me->localPos().y();
           if(!(this->editor->tiles_container_scene->is_empty())){
               tile_item* tile_clicked = this->editor->tiles_container_scene->tile_clicked(x, y);
               if(tile_clicked != NULL){
                   delete this->editor->tile_item_selected;
                   this->editor->tile_item_selected = tile_clicked;
                   this->editor->eraser_on = false;
               }
           }
           return true;
        }else{
            return QObject::eventFilter(obj, event);
        }
}
