QT += quick
CONFIG += c++11

INCLUDEPATH += -I /usr/local/ffepeg/include\
-I /usr/local/include \
-I /usr/local/include/jrtplib3/

LIBS += -L/usr/local/ffepeg/lib -lSDL2main -lSDL2 -lavformat  -lavcodec -lavutil -lm -lz -lswscale  -lswresample\
 -L/usr/local/lib -ltag -ltag_c\
-L/usr/local/lib -lz


INCLUDEPATH += /usr/include/mysql
LIBS += -L/usr/mysql -lmysqlclient_r

LIBS += -L /usr/include/boost -lboost_system
LIBS += /usr/lib/libpthread.so.0 -ljsoncpp

QT += multimedia
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    code/singer.cpp \
    code/songlist.cpp \
    code/music.cpp \
    code/mymusicplayer.cpp \
    code/client.cpp \
    code/myJson.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    code/singer.h \
    code/songlist.h \
    code/music.h \
    code/mymusicplayer.h \
    code/resolvemusic.h \
    code/client.h \
    code/file_info.h \
    code/myJson.h

DISTFILES += \
    最美.mp3

