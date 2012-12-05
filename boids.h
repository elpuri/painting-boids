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
