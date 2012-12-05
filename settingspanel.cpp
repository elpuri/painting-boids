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
#include <QFileDialog>

SettingsPanel::SettingsPanel(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    connect(sliderBoidCount, SIGNAL(valueChanged(int)), this, SIGNAL(boidCountChanged(int)));
    connect(sliderBoidCount, SIGNAL(valueChanged(int)), this, SLOT(onBoidCountChanged(int)));
    connect(sliderOpacity, SIGNAL(valueChanged(int)), this, SIGNAL(trailOpacityChanged(int)));
    connect(sliderColorEvolutionRate, SIGNAL(valueChanged(int)), this, SIGNAL(colorEvolutionRateChanged(int)));
    connect(sliderMaximumSpeed, SIGNAL(valueChanged(int)), this, SIGNAL(maximumSpeedChanged(int)));
    connect(sliderMinimumDistance, SIGNAL(valueChanged(int)), this, SIGNAL(minimumDistanceChanged(int)));
    connect(sliderInertia, SIGNAL(valueChanged(int)), this, SIGNAL(inertiaChanged(int)));

    connect(btnClear, SIGNAL(clicked()), this, SIGNAL(clearCanvas()));
    connect(btnSave, SIGNAL(clicked()), this, SLOT(onSaveCanvas()));
    connect(btnLoad, SIGNAL(clicked()), this, SLOT(onLoadTexture()));
    connect(btnQuit, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));

    connect(btnExact, SIGNAL(clicked()), &m_modeMapper, SLOT(map()));
    connect(btnConstantLine, SIGNAL(clicked()), &m_modeMapper, SLOT(map()));
    connect(btnEvolving, SIGNAL(clicked()), &m_modeMapper, SLOT(map()));
    m_modeMapper.setMapping(btnExact, Boids::ColoringExact);
    m_modeMapper.setMapping(btnConstantLine, Boids::ColoringConstantLine);
    m_modeMapper.setMapping(btnEvolving, Boids::ColoringEvolving);
    connect(&m_modeMapper, SIGNAL(mapped(int)), this, SLOT(onColoringModeChanged(int)));

    lblBoidCount->setText(QString::number(sliderBoidCount->value()));
}

void SettingsPanel::onLoadTexture()
{
    QString filename = QFileDialog::getOpenFileName(this, "Select texture", "pics/", ".jpg,*.png");
    emit textureChanged(filename);
}

void SettingsPanel::onSaveCanvas()
{
    QString filename = QFileDialog::getSaveFileName(NULL, "Save canvas", "", "*.png");
    if (!filename.endsWith(".png"))
        filename.append(".png");
    emit saveCanvas(filename);
}

void SettingsPanel::onColoringModeChanged(int mode)
{
    Boids::ColoringMode m = (Boids::ColoringMode) mode;
    sliderColorEvolutionRate->setEnabled(m == Boids::ColoringEvolving);
    emit coloringModeChanged(m);
}

void SettingsPanel::onBoidCountChanged(int count)
{
    lblBoidCount->setText(QString::number(sliderBoidCount->value()));
}

int SettingsPanel::maximumSpeed()
{
    return sliderMaximumSpeed->value();
}

int SettingsPanel::minimumDistance()
{
    return sliderMinimumDistance->value();
}

Boids::ColoringMode SettingsPanel::coloringMode() {
    if (btnExact->isChecked())
        return Boids::ColoringExact;
    else if (btnConstantLine->isChecked())
        return Boids::ColoringConstantLine;
    else if (btnEvolving->isChecked())
        return Boids::ColoringEvolving;

    Q_ASSERT(false);
    return Boids::ColoringEvolving;
}

int SettingsPanel::boidCount()
{
    return sliderBoidCount->value();
}

int SettingsPanel::colorEvolutionRate()
{
    return sliderColorEvolutionRate->value();
}

int SettingsPanel::trailOpacity()
{
    return sliderOpacity->value();
}

int SettingsPanel::inertia()
{
    return sliderInertia->value();
}
