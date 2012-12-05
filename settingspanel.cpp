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
