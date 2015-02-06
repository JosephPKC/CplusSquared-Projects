TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    airport.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    airport.h

