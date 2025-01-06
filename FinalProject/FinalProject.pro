QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Commands/attacknearestenemycommand.cpp \
    Commands/gotocommand.cpp \
    Commands/helpcommand.cpp \
    Commands/movedowncommand.cpp \
    Commands/moveleftcommand.cpp \
    Commands/moverightcommand.cpp \
    Commands/moveupcommand.cpp \
    Commands/takenearesthealthpackcommand.cpp \
    Controller/enemycontroller.cpp \
    Controller/inputcontroller.cpp \
    Controller/levelcontroller.cpp \
    Controller/pathfindercontroller.cpp \
    Controller/playercontroller.cpp \
    Model/enemywrapper.cpp \
    Model/node.cpp \
    Model/penemywrapper.cpp \
    Model/worldrevised.cpp \
    Model/xenemy.cpp \
    View/backgroundviewtext.cpp \
    View/enemyview2d.cpp \
    View/enemyviewtext.cpp \
    View/gameobject2dview.cpp \
    View/gameobjecttextview.cpp \
    View/healthpackview2d.cpp \
    View/healthpackviewtext.cpp \
    View/penemyview2d.cpp \
    View/penemyviewtext.cpp \
    View/protagonistview2d.cpp \
    View/protagonistviewtext.cpp \
    View/statusbar2d.cpp \
    View/worldview2d.cpp \
    View/worldviewtext.cpp \
    View/xenemyview2d.cpp \
    View/xenemyviewtext.cpp \
    Controller/gamecontroller.cpp \
    main.cpp \
    mainwindow.cpp \
    Model/player.cpp


HEADERS += \
    Commands/attacknearestenemycommand.h \
    Commands/command.h \
    Commands/gotocommand.h \
    Commands/helpcommand.h \
    Commands/movedowncommand.h \
    Commands/moveleftcommand.h \
    Commands/moverightcommand.h \
    Commands/moveupcommand.h \
    Commands/takenearesthealthpackcommand.h \
    Controller/enemycontroller.h \
    Controller/gameobjectcontroller.h \
    Controller/inputcontroller.h \
    Controller/levelcontroller.h \
    Controller/pathfindercontroller.h \
    Controller/playercontroller.h \
    Level.h \
    Model/enemywrapper.h \
    Model/node.h \
    Model/penemywrapper.h \
    Model/worldrevised.h \
    Model/xenemy.h \
    View/backgroundviewtext.h \
    View/enemyview2d.h \
    View/enemyviewtext.h \
    View/gameobject2dview.h \
    View/gameobjecttextview.h \
    View/healthpackview2d.h \
    View/healthpackviewtext.h \
    View/penemyview2d.h \
    View/penemyviewtext.h \
    View/protagonistview2d.h \
    View/protagonistviewtext.h \
    View/statusbar2d.h \
    View/worldview.h \
    View/worldview2d.h \
    View/worldviewtext.h \
    View/xenemyview2d.h \
    View/xenemyviewtext.h \
    Controller/gamecontroller.h \
    mainwindow.h \
    Model/player.h

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

QMAKE_CXXFLAGS += -fconcepts-diagnostics-depth=200

DISTFILES +=
