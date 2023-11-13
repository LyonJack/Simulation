#include "MapItem.h"
#include <QPainter>
#include <QColor>

MapItem::MapItem(QQuickItem* parent) :QQuickPaintedItem(parent)
{
    corePath = "Enclib";
    coreImortFile = "C1100101.X57";
    EnclSENCInit(corePath.toUtf8());
    EnclSENCS57ImportFile(coreImortFile.toUtf8());
    //EnclSENCMENCImportFile(coreImortFile.toUtf8());
    //EnclSENCS57ImportTree("");
    //EnclSENCMENCImportTree("");
}

void MapItem::onWheel(float pX,float pY,float dy)
{
    double zoomFactor = 1;
    if (dy > 0)
        zoomFactor = 1 / scale_factor;
    else
        zoomFactor = scale_factor;
    EnclViewZoom(pX, pY, zoomFactor);
    update();
}

void MapItem::paint(QPainter* painter)
{
    auto pPixBuf = EnclDrawChart();
    if (pPixBuf)
    {
        QImage img = QImage(pPixBuf, this->width(), this->height(), QImage::Format_RGB32);
        painter->drawImage(0, 0, img);
        m_storedviewImg = img.copy();
    }
    else
    {
        painter->drawImage(0, 0, m_storedviewImg);
    }
}
