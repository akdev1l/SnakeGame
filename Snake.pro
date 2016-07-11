TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    block.cpp \
    player.cpp

HEADERS += \
    block.h \
    player.h
LIBS += -lncurses
