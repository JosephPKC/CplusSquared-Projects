TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ListTools.h \
    stack.h \
    Queue.h \
    List.h \
    UniqueList.h \
    SortedList.h \
    UniqueSortedList.h \
    Frequency.h \
    Iterator.h

