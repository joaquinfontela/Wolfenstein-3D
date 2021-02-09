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
     std::string path;
     QGraphicsView* map;
public:
    tile_item(std::string path, int tipo, bool cumulative);
    /**
     * @brief make a copy of this tile item and get it pointer.
     *
     * @return a pointer to a tile_item.
     */
    tile_item* create_copy();

    /**
     * @brief set the map atributte.
     *
     * @param map a QGraphicView.
     */
    void add_to(QGraphicsView* map);

    /**
     * @param tile a pointer to a tile_item.
     *
     * @return return a bolean that represent if this tile and the
     * tile passed by param can be together in a cell.
     */
    bool accept_tile(tile_item* tile);
    int get_type();

    /**
     * @brief update the rect atributte.
     *
     * @param tile_size an int that represents the side size of the tile_item.
     * @param x a float that represent the x position where this will be painted.
     * @param y a float that represent the y position where this will be painted.
     */
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
