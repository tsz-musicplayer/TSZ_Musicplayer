TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

LIBS += -L /usr/include/boost -lboost_system
LIBS += /usr/lib/libpthread.so.0

HEADERS += \
    file_info.h
