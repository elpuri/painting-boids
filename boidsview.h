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
