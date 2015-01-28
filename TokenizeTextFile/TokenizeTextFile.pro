TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
SOURCES += main.cpp \
    token.cpp \
    stokenizer.cpp \
    ftokenizer.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    token.h \
    stokenizer.h \
    ftokenizer.h \
    ListTools.h \
    Frequency.h \
    NodePair.h \
    GenericFunctions.h

