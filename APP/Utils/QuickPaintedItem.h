#pragma once
#include <QPainterPath>
#include <QtQuick>

class QuickPaintedItem : public QQuickPaintedItem
{
    Q_OBJECT
        Q_PROPERTY(bool draw READ isDraw WRITE setDraw NOTIFY drawChanged)
        Q_PROPERTY(bool antialias READ isAntialias WRITE setAntialias NOTIFY antialiasChanged)

public:
    QuickPaintedItem(QQuickItem* parent = 0);
    void paint(QPainter* painter) override;

    Q_INVOKABLE void mousePress(qreal x, qreal y);
    Q_INVOKABLE void mouseMove(qreal x, qreal y);
    Q_INVOKABLE void mouseRelease(qreal x, qreal y);

    bool isDraw() const;
    void setDraw(bool newDraw);

    bool isAntialias() const;
    void setAntialias(bool newAntialias);

private:

signals:
    void drawChanged();

    void antialiasChanged();

private:
    bool draw;
    QPainterPath m_path;
    QPolygonF  m_poly;
};
