#include <QtGui>

#include "mapwidget.h"


MapWidget::MapWidget(QWidget *parent)
    : QWidget(parent)
{
    setAcceptDrops(true);
    setMinimumSize(Constantes::tamXMapa, Constantes::tamYMapa);
    setMaximumSize(Constantes::tamXMapa, Constantes::tamYMapa);
}

void MapWidget::clear()
{
    pieceLocations.clear();
    piecePixmaps.clear();
    pieceRects.clear();
    pieceIDs.clear();
    highlightedRect = QRect();
    inPlace = 0;
    update();
}

void MapWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece"))
        event->accept();
    else
        event->ignore();
}

void MapWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    QRect updateRect = highlightedRect;
    highlightedRect = QRect();
    update(updateRect);
    event->accept();
}

void MapWidget::dragMoveEvent(QDragMoveEvent *event)
{
    QRect updateRect = highlightedRect.unite(targetSquare(event->pos()));

    if (event->mimeData()->hasFormat("image/x-puzzle-piece")
        && findPiece(targetSquare(event->pos())) == -1) {

        highlightedRect = targetSquare(event->pos());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        highlightedRect = QRect();
        event->ignore();
    }

    update(updateRect);
}

void MapWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("image/x-puzzle-piece")
        && findPiece(targetSquare(event->pos())) == -1) {

        QByteArray pieceData = event->mimeData()->data("image/x-puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QRect square = targetSquare(event->pos());
        QPixmap pixmap;
        QPoint location;
        int id;
        dataStream >> pixmap >> location >> id;

        pieceLocations.append(location);
        piecePixmaps.append(pixmap);
        pieceRects.append(square);
        pieceIDs.append(id);

        highlightedRect = QRect();
        update(square);

        event->setDropAction(Qt::MoveAction);
        event->accept();

        inPlace++;
        emit mapchanged();

        if (inPlace == Constantes::totalSquares){
            emit mapCompleted();
        }

     } else {
        highlightedRect = QRect();
        event->ignore();
     }
}

int MapWidget::findPiece(const QRect &pieceRect) const
{
    for (int i = 0; i < pieceRects.size(); ++i) {
        if (pieceRect == pieceRects[i]) {
            return i;
        }
    }
    return -1;
}

void MapWidget::mousePressEvent(QMouseEvent *event)
{
    QRect square = targetSquare(event->pos());
    int found = findPiece(square);

    if (found == -1)
        return;

    QPoint location = pieceLocations[found];
    QPixmap pixmap = piecePixmaps[found];
    int id = pieceIDs[found];

    pieceLocations.removeAt(found);
    piecePixmaps.removeAt(found);
    pieceRects.removeAt(found);
    pieceIDs.removeAt(found);

    inPlace--;

    update(square);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    dataStream << pixmap << location << id;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("image/x-puzzle-piece", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos() - square.topLeft());
    drag->setPixmap(pixmap);

    if (!(drag->exec(Qt::MoveAction) == Qt::MoveAction)) {
        pieceLocations.insert(found, location);
        piecePixmaps.insert(found, pixmap);
        pieceRects.insert(found, square);
        pieceIDs.insert(found, id);
        update(targetSquare(event->pos()));


        inPlace++;

    }
}

void MapWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(event->rect(), Qt::white);

    if (highlightedRect.isValid()) {
        //painter.setBrush(QColor("#ffcccc"));
        painter.setBrush(QColor("#5581E1"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }

    for (int i = 0; i < pieceRects.size(); ++i) {
        painter.drawPixmap(pieceRects[i], piecePixmaps[i].scaled(QSize(Constantes::intIconSize, Constantes::intIconSize),Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
    painter.end();
}

const QRect MapWidget::targetSquare(const QPoint &position) const
{
    return QRect(position.x()/Constantes::sizeSquare * Constantes::sizeSquare, position.y()/Constantes::sizeSquare * Constantes::sizeSquare, Constantes::sizeSquare, Constantes::sizeSquare);
}

int MapWidget::getInPlace(){
    return inPlace;
}
