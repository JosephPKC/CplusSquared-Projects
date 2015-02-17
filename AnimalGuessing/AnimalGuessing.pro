TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
SOURCES += main.cpp \
    ftokenizer.cpp \
    stokenizer.cpp \
    token.cpp

HEADERS += \
    BinaryTree.h \
    Utilities.h \
    ftokenizer.h \
    NodePair.h \
    stokenizer.h \
    token.h \
    ../Lists/Iterator.h \
    ../Lists/ListTools.h \
    ../Lists/stack.h \
    Iterator.h \
    ListTools.h \
    stack.h

