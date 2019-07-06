TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    code/session.cpp \
    code/server.cpp \
    code/mydb.cpp \
    code/myJson.cpp

HEADERS += \
    code/session.h \
    code/server.h \
    code/file_info.h \
    code/mydb.h \
    code/myJson.h

INCLUDEPATH += /usr/include/mysql
LIBS += -L/usr/mysql -lmysqlclient_r

#LIBS += -L /usr/lib/  -ljsoncpp

LIBS += -L /usr/include/boost -lboost_system
LIBS += /usr/lib/libpthread.so.0 -ljsoncpp


