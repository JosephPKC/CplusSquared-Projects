TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    BinarySearchTree.h \
    BinaryTreeTools.h \
    Heap.h \
    BTree.h \
    Set.h

