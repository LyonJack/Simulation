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

    QString corePath;		   //��ͼ����Ŀ¼
    QString coreImortFile;     //��ͼ�����ļ�
    double scale_factor = 0.5; //��ͼ����ϵ��
    QImage m_storedviewImg;

    // ͨ�� QQuickPaintedItem �̳�
    void paint(QPainter* painter) override;
};
