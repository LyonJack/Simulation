#pragma once
#include <encl.h>
#include <qstring.h>
#include <qimage.h>
#include <QQuickItem>
#include <QQuickPaintedItem>
#include <qobject.h>

class MapItem :public QQuickPaintedItem
{
    Q_OBJECT
public:
    MapItem(QQuickItem* parent = nullptr);

    Q_INVOKABLE void onWheel(float pX,float pY,float dy);
private:

    QString corePath;		   //海图核心目录
    QString coreImortFile;     //海图数据文件
    double scale_factor = 0.5; //海图缩放系数
    QImage m_storedviewImg;

    // 通过 QQuickPaintedItem 继承
    void paint(QPainter* painter) override;
};
