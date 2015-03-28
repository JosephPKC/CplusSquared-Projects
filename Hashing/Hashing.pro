TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    HTable.h \
    Iterator.h \
    List.h \
    ListTools.h

