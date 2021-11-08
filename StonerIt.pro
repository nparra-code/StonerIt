QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    character.cpp \
    enemy.cpp \
    hero.cpp \
    main.cpp \
    map.cpp \
    sonerit.cpp \
    sprite.cpp

HEADERS += \
    character.h \
    enemy.h \
    hero.h \
    map.h \
    movement.h \
    sonerit.h \
    sprite.h

FORMS += \
    sonerit.ui

TRANSLATIONS += \
    StonerIt_es_CO.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pictures.qrc

DISTFILES += \
    BD/hSprite.png
