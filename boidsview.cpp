#include "boidsview.h"
#include <QDebug>
#include <QMouseEvent>

BoidsView::BoidsView(QPixmap* bg)
{
    m_canvas = bg;
    setMouseTracking(true);    
    m_running = false;
}

void BoidsView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF mapped = mapToScene(event->x(), event->y()); 
    emit mousePositionChanged(mapped.x(), mapped.y());
}

void BoidsView::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(-width() / 2, -height() / 2, *m_canvas);
}

void BoidsView::resizeEvent(QResizeEvent *event)
{
    int w = width();
    int h = height();
    setSceneRect(-w / 2, -h / 2, w, h);
}

void BoidsView::canvasChanged(QPixmap *canvas)
{
    m_canvas = canvas;
    int w = canvas->width();
    int h = canvas->height();
    resize(w, h);
}

void BoidsView::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        m_running = !m_running;
        emit enableSimulation(m_running);
    }
}

