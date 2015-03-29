TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
SOURCES += main.cpp \
    book.cpp \
    bookcatalogue.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    HTable.h \
    Iterator.h \
    List.h \
    ListTools.h \
    book.h \
    bookcatalogue.h

