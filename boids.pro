#-------------------------------------------------
#
# Project created by QtCreator 2012-08-15T19:38:04
#
#-------------------------------------------------

QT += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
}

TARGET = boids
TEMPLATE = app


SOURCES += main.cpp \
    boids.cpp \
    boidsview.cpp \
    settingspanel.cpp

HEADERS += \
    boids.h \
    boidsview.h \
    settingspanel.h

FORMS += \
    settings.ui

OTHER_FILES += \
    README.md




