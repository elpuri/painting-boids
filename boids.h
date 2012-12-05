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

#ifndef BOIDS_H
#define BOIDS_H

#include <QObject>
#include <QList>
#include <QGraphicsItem>
#include <QVector2D>
#include <QPen>
#include <QBrush>
#include <QColor>


class QGraphicsScene;
class QPixmap;



class Boid : public QGraphicsItem {
    protected:
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        QRectF boundingRect() const { return QRectF(-10, -10, 20, 20); }
    public:
        QVector2D m_velocity;
        QVector2D m_position;
        QColor m_color;
};



class Boids : public QObject
{
    Q_OBJECT
public:
    enum ColoringMode { ColoringExact, ColoringConstantLine, ColoringEvolving };

    explicit Boids(QGraphicsScene* scene, QPixmap* bg, QImage* pattern, QObject *parent = 0);

signals:
    void canvasChanged(QPixmap* canvas);

public slots:
    void setTargetLocation(float x, float y);       // in scene coordinates
    void enableSimulation(bool enable);
    void setBoidCount(int newCount);
    void setColorEvolutionRate(int rate);
    void setTrailOpacity(int opacity);
    void clearCanvas();
    void saveCanvas(QString filename);
    void loadTexture(QString filename);
    void setColoringMode(Boids::ColoringMode mode);
    void setMaxBoidSpeed(int speed);
    void setMinimumDistance(int distance);
    void setInertia(int inertia);

private:
    void timerEvent(QTimerEvent *);
    QVector2D tendToCenterOfFlock(Boid* boid);
    QVector2D keepDistance(Boid* boid);
    QVector2D matchVelocity(Boid* boid);
    QVector2D tendToLocation(const QVector2D p, Boid* boid);

    void removeBoids(int count);
    void addBoids(int count);



private:

    QList<Boid*> m_boids;
    QPixmap* m_canvas;
    QImage* m_pattern;
    QGraphicsScene* m_scene;
    float m_targetX, m_targetY;
    QPen m_pen;
    QBrush m_picBrush;
    bool m_simulationRunning;
    qreal m_trailOpacity;
    qreal m_colorEvolutionRate;
    qreal m_maxSpeed;
    qreal m_minimumDistance;
    qreal m_inertiaFactor;
    ColoringMode m_coloringMode;
};

#endif // BOIDS_H
