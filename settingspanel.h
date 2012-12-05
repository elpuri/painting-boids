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
