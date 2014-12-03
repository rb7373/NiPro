#ifndef PIECESLIST_H
#define PIECESLIST_H

#include <QListWidget>

#include "constantes.h"

class ObstaclesList : public QListWidget
{
    Q_OBJECT

public:
    ObstaclesList(QWidget *parent = 0);
    void addPiece(QPixmap pixmap, QPoint location, int pId);
    void addPiece(QPixmap pixmap, QPoint location, int pId, int pRow);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void startDrag(Qt::DropActions supportedActions);

private:
};

#endif
