#pragma once
#include <encl.h>
#include <qstring.h>
#include <qimage.h>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include <qobject.h>
#include "propertyHeader.h"

class MapItem :public QQuickPaintedItem
{
    Q_OBJECT
    BJ_PROPERTY(double, centerFreqPos)
    BJ_PROPERTY(double, spanFreqPos)
    BJ_PROPERTY(double, bandPowerPos)
public:
    MapItem(QQuickItem* parent = nullptr);
    ~MapItem();

private:

    QString corePath;		//海图核心目录
    QString coreImortFile;  //海图数据文件
    QImage m_storedviewImg;

    // 通过 QQuickPaintedItem 继承
    void paint(QPainter* painter) override;
signals:
    void centerFreqPosChanged(const double&);
    void spanFreqPosChanged(const double&);
    void bandPowerPosChanged(const double&);
};
