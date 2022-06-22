QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boss.cpp \
    editvendor.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    manager.cpp \
    marketologist.cpp \
    seller.cpp

HEADERS += \
    boss.h \
    editvendor.h \
    login.h \
    mainwindow.h \
    manager.h \
    marketologist.h \
    seller.h

FORMS += \
    boss.ui \
    editvendor.ui \
    login.ui \
    mainwindow.ui \
    manager.ui \
    marketologist.ui \
    seller.ui

RC_ICONS += main.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


