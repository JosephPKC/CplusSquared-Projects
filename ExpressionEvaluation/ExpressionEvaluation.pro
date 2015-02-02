TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
SOURCES += main.cpp \
    expressionevaluator.cpp \
    stokenizer.cpp \
    token.cpp

HEADERS += \
    expressionevaluator.h \
    ListTools.h \
    stack.h \
    stokenizer.h \
    token.h \
    Iterator.h

