#ifndef TILE_CONTAINER_ACTIONS_H
#define TILE_CONTAINER_ACTIONS_H

#include <QObject>
#include "tiles_container.h"
#include "editor.h"
#include "ui_editor.h"

class tile_container_actions : public QObject
{
        Q_OBJECT
public:
    tile_container_actions(Editor* editor);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
private:
    Editor* editor;
};

#endif // TILE_CONTAINER_ACTIONS_H
