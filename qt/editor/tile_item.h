#ifndef TILE_ITEM_H
#define TILE_ITEM_H

#include <QGraphicsItem>
#include <QLabel>
#include <QString>
#include <QGraphicsView>

class tile_item : public QGraphicsItem
{
     int type;
     QImage my_image;
     QRect my_rect;
     QString path;
     QGraphicsView* map;
public:
    tile_item(QString path, int tipo, bool cumulative);
    tile_item* create_copy();
    void add_to(QGraphicsView* map);
    bool accept_tile(tile_item* tile);
    int get_type();
    void configure_rect(int tile_size = 0, float x = -1, float y = -1);
    QRectF boundingRect() const override;

    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget) override;

     bool cumulative;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // TILE_ITEM_H
