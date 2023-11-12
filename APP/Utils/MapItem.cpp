#include "MapItem.h"
#include <QPainter>
#include <QColor>

MapItem::MapItem(QQuickItem* parent):QQuickPaintedItem(parent)
{
    //connect(this, &MapItem::centerFreqPosChanged, this, &MapItem::set_centerFreqPos);
    //connect(this, &MapItem::spanFreqPosChanged, this, &MapItem::set_spanFreqPos);
    //connect(this, &MapItem::bandPowerPosChanged, this, &MapItem::set_bandPowerPos);
    corePath = "Enclib";
    coreImortFile = "";
    EnclSENCInit(corePath.toUtf8());
    EnclSENCS57ImportFile(coreImortFile.toUtf8());
    EnclSENCMENCImportFile(coreImortFile.toUtf8());
    //EnclSENCS57ImportTree("");
    //EnclSENCMENCImportTree("");
}

MapItem::~MapItem()
{
}

void MapItem::paint(QPainter* painter)
{
    //auto pPixBuf = EnclDrawChart();
    //if (pPixBuf)
    //{
    //    QImage img = QImage(pPixBuf, this->width(), this->height(), QImage::Format_RGB32);
    //    painter->drawImage(0, 0, img);
    //    m_storedviewImg = img.copy();
    //}
    //else
    //{
    //    painter->drawImage(0, 0, m_storedviewImg);
    //}
    if(painter == nullptr)
        return;

    painter->save();

    double dStartFreqPos = m_centerFreqPos - m_spanFreqPos / 2;
    double dStopFreqPos = m_centerFreqPos + m_spanFreqPos / 2;

    painter->setPen(Qt::blue);
    //画线
    painter->drawLine(QPointF(dStartFreqPos,0),QPointF(dStartFreqPos,height()));
    painter->drawLine(QPointF(dStopFreqPos,0),QPointF(dStopFreqPos,height()));
    painter->drawLine(QPointF(dStartFreqPos,m_bandPowerPos),QPointF(dStopFreqPos,m_bandPowerPos));

    //画字体
    int nTextHeight = 15;
    QFont ft;
    ft.setPixelSize(nTextHeight);
    painter->setFont(ft);
    painter->drawText(QRectF(QPointF(dStartFreqPos,m_bandPowerPos - nTextHeight),QSizeF(m_spanFreqPos,nTextHeight)),
                      Qt::AlignHCenter | Qt::AlignBottom,
                      QString("BW:%1").arg(m_bandPowerPos));

    painter->restore();
}
