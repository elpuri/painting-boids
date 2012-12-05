/*
 Copyright (c) 2012, Juha Turunen
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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

