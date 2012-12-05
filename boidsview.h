#ifndef BOIDSVIEW_H
#define BOIDSVIEW_H

#include <QGraphicsView>
#include <QPixmap>
#include <QImage>

class Boids;

class BoidsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit BoidsView(QPixmap* bg);

    void mouseMoveEvent(QMouseEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);
    void mousePressEvent(QMouseEvent *event);

protected:
    void resizeEvent(QResizeEvent *event);

signals:
    void mousePositionChanged(float x, float y);    // In scene coordinates
    void repainted();
    void enableSimulation(bool enable);

public slots:
    void canvasChanged(QPixmap* canvas);

private:
    QPixmap* m_canvas;
    bool m_running;

};

#endif // BOIDSVIEW_H
