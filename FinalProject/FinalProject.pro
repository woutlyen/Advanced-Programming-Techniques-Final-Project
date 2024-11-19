QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/enemycontroller.cpp \
    Controller/penemycontroller.cpp \
    Controller/playercontroller.cpp \
    Controller/xenemycontroller.cpp \
    View/enemyview.cpp \
    View/enemyview2d.cpp \
    View/enemyviewtext.cpp \
    View/healthpackview.cpp \
    View/healthpackview2d.cpp \
    View/healthpackviewtext.cpp \
    View/penemyview.cpp \
    View/penemyview2d.cpp \
    View/penemyviewtext.cpp \
    View/protagonistview2d.cpp \
    View/protagonistviewtext.cpp \
    View/tileview.cpp \
    View/worldview2d.cpp \
    View/worldviewtext.cpp \
    View/xenemyview.cpp \
    View/xenemyview2d.cpp \
    View/xenemyviewtext.cpp \
    Controller/gamecontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    View/worldview.cpp \
    View/protagonistview.cpp \


HEADERS += \
    Controller/enemycontroller.h \
    Controller/penemycontroller.h \
    Controller/playercontroller.h \
    Controller/xenemycontroller.h \
    View/enemyview.h \
    View/enemyview2d.h \
    View/enemyviewtext.h \
    View/healthpackview.h \
    View/healthpackview2d.h \
    View/healthpackviewtext.h \
    View/penemyview.h \
    View/penemyview2d.h \
    View/penemyviewtext.h \
    View/protagonistview2d.h \
    View/protagonistviewtext.h \
    View/tileview.h \
    View/worldview2d.h \
    View/worldviewtext.h \
    View/xenemyview.h \
    View/xenemyview2d.h \
    View/xenemyviewtext.h \
    Controller/gamecontroller.h \
    mainwindow.h \
    View/worldview.h \
    View/protagonistview.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/../worldlib/ -lworld

INCLUDEPATH += $$PWD/../worldlib_source
DEPENDPATH += $$PWD/../worldlib_source

RESOURCES += \
    images.qrc
