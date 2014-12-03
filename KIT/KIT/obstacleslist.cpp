#include <QtGui>

#include "obstacleslist.h"

ObstaclesList::ObstaclesList(QWidget *parent)
    : QListWidget(parent)
{

    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(Constantes::intIconSize, Constantes::intIconSize));
    setSpacing(10);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setMaximumSize(120,400);
    setMinimumSize(120,400);
    //setSortingEnabled(true);
    //setFocusPolicy(Qt::NoFocus);

}

void ObstaclesList::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
    {
        event->accept();
    }

    else
    {
        event->ignore();
    }
}

void ObstaclesList::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else
        event->ignore();
}

void ObstaclesList::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")) {
        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QPixmap pixmap;
        QPoint location;
        int id;
        dataStream >> pixmap >> location >> id;

        //Casos especiales
        //se permiten volver a insertar
        if (id == 0 || id == 1)
        {
            addPiece(pixmap, location, id, 0);
        }
        //        addPiece(pixmap, location, id);

        event->setDropAction(Qt::MoveAction);
        event->accept();
        //qDebug() << "Insertando";

    } else
        event->ignore();
}

void ObstaclesList::addPiece(QPixmap pixmap,
                             QPoint location,
                             int pId)
{
    QListWidgetItem *pieceItem = new QListWidgetItem(this);
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole+1, location);
    pieceItem->setData(Qt::UserRole+2, pId);
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable
                        | Qt::ItemIsDragEnabled);

}

void ObstaclesList::addPiece(QPixmap pixmap,
                             QPoint location,
                             int pId,
                             int pRow)
{
    QListWidgetItem *pieceItem = new QListWidgetItem();
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole+1, location);
    pieceItem->setData(Qt::UserRole+2, pId);
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable
                        | Qt::ItemIsDragEnabled);

    insertItem(pRow,pieceItem);

}

void ObstaclesList::startDrag(Qt::DropActions /*supportedActions*/)
{
    QListWidgetItem *item = currentItem();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qVariantValue<QPixmap>(item->data(Qt::UserRole));
    QPoint location = item->data(Qt::UserRole+1).toPoint();
    int id = item->data(Qt::UserRole+2).toInt();
    dataStream << pixmap << location << id;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("image/x-puzzle-piece", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    drag->setPixmap(pixmap);

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
    {

        //Casos especiales
        //se permiten borrar
        if (id == 0 || id == 1)
        {
            delete takeItem(row(item));
        }

        //No borrar el item viejo
        //delete takeItem(row(item));
    }

}
