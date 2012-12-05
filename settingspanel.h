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

#ifndef SETTINGSPANEL_H
#define SETTINGSPANEL_H

#include <QWidget>
#include <QSignalMapper>
#include "ui_settings.h"
#include "boids.h"

class SettingsPanel : public QWidget, private Ui_SettingsForm
{
    Q_OBJECT


public:
    explicit SettingsPanel(QWidget *parent = 0);

    Boids::ColoringMode coloringMode();
    int boidCount();
    int colorEvolutionRate();
    int trailOpacity();
    int maximumSpeed();
    int minimumDistance();
    int inertia();

signals:
    void boidCountChanged(int count);
    void trailOpacityChanged(int opacity);
    void clearCanvas();
    void saveCanvas(QString filename);
    void textureChanged(QString filename);
    void colorEvolutionRateChanged(int rate);
    void coloringModeChanged(Boids::ColoringMode mode);
    void maximumSpeedChanged(int value);
    void minimumDistanceChanged(int value);
    void inertiaChanged(int value);

public slots:
    void onLoadTexture();
    void onSaveCanvas();
    void onColoringModeChanged(int);
    void onBoidCountChanged(int);

private:
    QSignalMapper m_modeMapper;
};

#endif // SETTINGSPANEL_H
