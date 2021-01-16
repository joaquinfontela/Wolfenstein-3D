#ifndef MOUSETILEACTIONS_H
#define MOUSETILEACTIONS_H
#include <QObject>
#include "tiles_container.h"
#include "editor.h"

class mouseTileActions : public QObject
{
    Q_OBJECT

public:
    mouseTileActions(Editor* editor);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
private:
    tiles_container* tc;
    Editor* editor;
};

#endif // MOUSETILEACTIONS_H
