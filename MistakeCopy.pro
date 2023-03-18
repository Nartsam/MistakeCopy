QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adddialog.cpp \
    codec.cpp \
    globalsignal.cpp \
    main.cpp \
    mainwindow.cpp \
    mtextedit.cpp \
    question.cpp \
    viewdialog.cpp

HEADERS += \
    adddialog.h \
    codec.h \
    globalsignal.h \
    mainwindow.h \
    mlog.h \
    mtextedit.h \
    question.h \
    viewdialog.h

FORMS += \
    adddialog.ui \
    mainwindow.ui \
    viewdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
