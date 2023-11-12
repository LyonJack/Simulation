#include "QuickPaintedItem.h"
#include <QDebug>
#define qout if( 1 ) qDebug()

static QPointF startPoint, lastPoint;
QuickPaintedItem::QuickPaintedItem(QQuickItem* parent)
    : QQuickPaintedItem(parent)
    , draw(false)
{
}

void QuickPaintedItem::paint(QPainter* painter)
{
    painter->drawPath(m_path);
    painter->drawPolyline(m_poly);

    if (startPoint.isNull() || lastPoint.isNull())
        return;

    if (draw) {
        painter->setPen(Qt::red);
        painter->drawLine(startPoint, lastPoint);
    }
}

void QuickPaintedItem::mousePress(qreal x, qreal y)
{
    startPoint.rx() = x;
    startPoint.ry() = y;
    if (draw) {
        m_path.addRect(x - 1, y - 1, 2, 2);
        m_poly.append(startPoint);
        update();
    }
}

void QuickPaintedItem::mouseMove(qreal x, qreal y)
{
    lastPoint.rx() = x;
    lastPoint.ry() = y;
    update();
}

void QuickPaintedItem::mouseRelease(qreal x, qreal y)
{
    if (draw) {
        lastPoint.rx() = x;
        lastPoint.ry() = y;
    }
    else {

    }
    update();
}

bool QuickPaintedItem::isDraw() const
{
    return draw;
}

void QuickPaintedItem::setDraw(bool newDraw)
{
    if (newDraw == false) {
        startPoint = lastPoint = QPointF();
        m_path.addPolygon(m_poly);
        m_path.closeSubpath();
        m_poly = QPolygonF();
        update();
    }
    if (draw == newDraw)
        return;
    draw = newDraw;


    emit drawChanged();
}

bool QuickPaintedItem::isAntialias() const
{
    return antialiasing();
}

void QuickPaintedItem::setAntialias(bool newAntialias)
{
    if (antialiasing() == newAntialias)
        return;
    setAntialiasing(newAntialias);
    emit antialiasChanged();
}
