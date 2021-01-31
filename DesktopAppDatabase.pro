QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buch.cpp \
    choice.cpp \
    karteikarte.cpp \
    lektion.cpp \
    lueckentext.cpp \
    main.cpp \
    mainwindow.cpp \
    unit.cpp

HEADERS += \
    buch.h \
    choice.h \
    karteikarte.h \
    lektion.h \
    lueckentext.h \
    mainwindow.h \
    unit.h

FORMS += \
    buch.ui \
    choice.ui \
    karteikarte.ui \
    lektion.ui \
    lueckentext.ui \
    mainwindow.ui \
    unit.ui

QMAKE_CXXFLAGS += -std=gnu++11

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
