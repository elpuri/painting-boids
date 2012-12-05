#include "boids.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPolygon>
#include <QPainter>
#include <QDebug>
#include <QFileDialog>
#include <stdlib.h>
#include <math.h>

QPolygon boidPolygon;

#define random() ((double) rand() / (double) RAND_MAX)

Boids::Boids(QGraphicsScene* scene, QPixmap* bg, QImage* pattern, QObject *parent) :
    QObject(parent)
{
    m_targetX = 0;
    m_targetY = 0;
    m_trailOpacity = 1.0;
    m_colorEvolutionRate = 0.5;
    m_pattern = pattern;
    boidPolygon.append(QPoint(0, -7));
    boidPolygon.append(QPoint(7, 7));
    boidPolygon.append(QPoint(-7, 7));
    m_canvas = bg;
    m_inertiaFactor = 0.5;
    clearCanvas();

    m_picBrush.setTextureImage(*m_pattern);
    m_pen.setBrush(m_picBrush);

    m_scene = scene;
    addBoids(50);
    startTimer(15);
    m_simulationRunning = false;
}

void Boids::clearCanvas()
{
    QPainter p(m_canvas);
    p.fillRect(0, 0, m_canvas->width(), m_canvas->height(), QColor(0, 0, 0));
}

void Boids::setTrailOpacity(int opacity)
{
    m_trailOpacity = (qreal) opacity  / 100.0;
}

void Boids::setColorEvolutionRate(int rate)
{
    m_colorEvolutionRate = (qreal) rate / 100.0;
}

void Boids::addBoids(int count)
{
    for (int i=0; i < count; i++) {
        Boid* boid = new Boid();
        boid->m_position = QVector2D((random() - 0.5) * m_pattern->width(), (random() - 0.5) * m_pattern->height());
        boid->setPos(boid->m_position.x(), boid->m_position.y());
        m_boids.append(boid);
        m_scene->addItem(boid);
    }
}

void Boids::removeBoids(int count)
{
    for (int i=0; i < count; i++) {
        Boid* boid = m_boids.takeFirst();
        m_scene->removeItem(boid);
        delete boid;
    }
}

void Boids::setBoidCount(int newCount)
{
    int count = newCount - m_boids.count();

    if (count > 0)
        addBoids(count);
    else if (count < 0)
        removeBoids(-count);    
}


void Boids::enableSimulation(bool enable)
{    
    m_simulationRunning = enable;
}

void Boids::timerEvent(QTimerEvent *)
{
    if (!m_simulationRunning)
        return;

    QPainter p(m_canvas);
    p.setPen(m_pen);
    p.setRenderHints(QPainter::Antialiasing, true);    
    p.setOpacity(m_trailOpacity);

    foreach(Boid* boid, m_boids) {

        QVector2D velocityDelta(0, 0);
        if (m_boids.count() > 1) {
            velocityDelta = tendToCenterOfFlock(boid);
            velocityDelta += keepDistance(boid);
            velocityDelta += matchVelocity(boid);
        }
        velocityDelta += tendToLocation(QVector2D(m_targetX, m_targetY), boid);

        boid->m_velocity += velocityDelta * m_inertiaFactor;

        float velocity = boid->m_velocity.length();        
        if (velocity > m_maxSpeed) {
            boid->m_velocity = boid->m_velocity / velocity * m_maxSpeed;
        }

        float angle = atan2(boid->m_velocity.y(), boid->m_velocity.x()) / 3.1415 * 180.0 + 90.0;
        boid->setRotation(angle);

        QVector2D midPoint(m_canvas->width() / 2, m_canvas->height() / 2);
        QVector2D oldPos = boid->m_position + midPoint;
        boid->m_position += boid->m_velocity;
        boid->setPos(boid->m_position.x(), boid->m_position.y());            
        QVector2D newPos = boid->m_position + midPoint;

        if (newPos.x() >= 0 && newPos.x() < m_canvas->width() && newPos.y() >= 0 && newPos.y() < m_canvas->height()) {
            int pix = m_pattern->pixel(newPos.x(), newPos.y());

            boid->m_color.setRed(qRed(pix) * m_colorEvolutionRate + boid->m_color.red() * (1.0 - m_colorEvolutionRate));
            boid->m_color.setGreen(qGreen(pix) * m_colorEvolutionRate + boid->m_color.green() * (1.0 - m_colorEvolutionRate));
            boid->m_color.setBlue(qBlue(pix) * m_colorEvolutionRate + boid->m_color.blue() * (1.0 - m_colorEvolutionRate));


            QPen pen(boid->m_color);
            p.setPen(pen);

            p.drawLine(oldPos.x(), oldPos.y(), newPos.x(), newPos.y());
        }

    }
}


QVector2D Boids::tendToCenterOfFlock(Boid *boid)
{
    QVector2D centerOfMass(0, 0);
    foreach(Boid* b, m_boids) {
        if (b != boid)
            centerOfMass += b->m_position;
    }
    centerOfMass /= (double) (m_boids.count() - 1);
    QVector2D v = centerOfMass - boid->m_position;
    v *= 0.0005;
    return v;
}

QVector2D Boids::tendToLocation(const QVector2D p, Boid *boid)
{
    QVector2D v = p - boid->m_position;
    return v / 300.0;
}

QVector2D Boids::keepDistance(Boid *boid)
{
    QVector2D c(0, 0);
    foreach(Boid* b, m_boids) {
        if (b != boid) {
            QVector2D d = b->m_position - boid->m_position;            
            float length = d.length();
            float factor = (m_minimumDistance - (m_minimumDistance < length ? m_minimumDistance : length)) / m_minimumDistance;
            c -= d * factor;
        }
    }
    return c;
}

QVector2D Boids::matchVelocity(Boid *boid)
{
    QVector2D averageVelocity(0, 0);

    foreach(Boid *b, m_boids) {
        if (b != boid) {
            averageVelocity += b->m_velocity;
        }
    }

    averageVelocity /= (double) (m_boids.count() - 1);
    QVector2D m_colorEvolutionRate = (boid->m_velocity - averageVelocity) * 0.025;
    return m_colorEvolutionRate;
}

void Boids::setTargetLocation(float x, float y)
{
    m_targetX = x;
    m_targetY = y;
}

void Boids::saveCanvas(QString filename)
{
    m_canvas->save(filename);
}

void Boids::setColoringMode(ColoringMode mode)
{
    m_coloringMode = mode;
}

void Boids::setMaxBoidSpeed(int speed)
{
    m_maxSpeed = speed * 0.01 * 9.0 + 1.0;
}

void Boids::setMinimumDistance(int distance)
{
    m_minimumDistance = distance * 0.5 + 15.0;
}

void Boids::setInertia(int inertia)
{
    m_inertiaFactor = 1.0 - inertia * 0.009;
}

void Boids::loadTexture(QString filename)
{
    m_pattern->load(filename);
    m_picBrush.setTextureImage(*m_pattern);
    m_pen.setBrush(m_picBrush);
    delete m_canvas;
    int w = m_pattern->width();
    int h = m_pattern->height();
    m_canvas = new QPixmap(w, h);
    clearCanvas();
    emit canvasChanged(m_canvas);
}

void Boid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush b(Qt::white);
    QPen p(Qt::black);
    painter->setBrush(b);
    painter->setPen(p);
    painter->setOpacity(0.5);
    painter->drawConvexPolygon(boidPolygon);
}
