#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGLWidget>
#include <QImage>
#include <QDebug>
#include "boids.h"
#include "boidsview.h"
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

#include "settingspanel.h"

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);

    QImage texture("pics/nana.jpg");
    if (texture.isNull()) {
        qDebug() << "Couldn't read the default texture. Shadow building, but forgot to set the run directory?";
        return 0;
    }
    QPixmap *canvas = new QPixmap(texture.width(), texture.height());

    QGraphicsScene scene;
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    Boids boids(&scene, canvas, &texture);


    SettingsPanel settings;
    settings.move(1250, 200);

    BoidsView view(canvas);


    QGLWidget* viewport = new QGLWidget();
    view.setViewport(viewport);
    view.setOptimizationFlag(QGraphicsView::DontSavePainterState);

    view.setAutoFillBackground(false);
    view.setGeometry(50, 100, texture.width(), texture.height());
    view.setScene(&scene);
    view.setSceneRect(-view.width() / 2, -view.height() / 2, view.width(), view.height());
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setWindowTitle("Boids");

    QObject::connect(&view, SIGNAL(mousePositionChanged(float,float)), &boids, SLOT(setTargetLocation(float,float)));
    QObject::connect(&view, SIGNAL(enableSimulation(bool)), &boids, SLOT(enableSimulation(bool)));
    QObject::connect(&settings, SIGNAL(boidCountChanged(int)), &boids, SLOT(setBoidCount(int)));
    QObject::connect(&settings, SIGNAL(trailOpacityChanged(int)), &boids, SLOT(setTrailOpacity(int)));
    QObject::connect(&settings, SIGNAL(textureChanged(QString)), &boids, SLOT(loadTexture(QString)));
    QObject::connect(&settings, SIGNAL(clearCanvas()), &boids, SLOT(clearCanvas()));
    QObject::connect(&settings, SIGNAL(saveCanvas(QString)), &boids, SLOT(saveCanvas(QString)));
    QObject::connect(&settings, SIGNAL(colorEvolutionRateChanged(int)), &boids, SLOT(setColorEvolutionRate(int)));
    QObject::connect(&settings, SIGNAL(coloringModeChanged(Boids::ColoringMode)), &boids, SLOT(setColoringMode(Boids::ColoringMode)));
    QObject::connect(&boids, SIGNAL(canvasChanged(QPixmap*)), &view, SLOT(canvasChanged(QPixmap*)));
    QObject::connect(&settings, SIGNAL(maximumSpeedChanged(int)), &boids, SLOT(setMaxBoidSpeed(int)));
    QObject::connect(&settings, SIGNAL(minimumDistanceChanged(int)), &boids, SLOT(setMinimumDistance(int)));
    QObject::connect(&settings, SIGNAL(inertiaChanged(int)), &boids, SLOT(setInertia(int)));

    boids.setBoidCount(settings.boidCount());
    boids.setColorEvolutionRate(settings.colorEvolutionRate());
    boids.setColoringMode(settings.coloringMode());
    boids.setTrailOpacity(settings.trailOpacity());
    boids.setMaxBoidSpeed(settings.maximumSpeed());
    boids.setMinimumDistance(settings.minimumDistance());
    boids.setInertia(settings.inertia());

    view.show();
    settings.show();
    return a.exec();
}
