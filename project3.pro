QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    forget_pass.cpp \
    main.cpp \
    mainwindow.cpp \
    profile_u.cpp \
    registration.cpp \
    user.cpp

HEADERS += \
    admin.h \
    forget_pass.h \
    libraries.h \
    mainwindow.h \
    profile_u.h \
    registration.h \
    user.h

FORMS += \
    admin.ui \
    forget_pass.ui \
    mainwindow.ui \
    profile_u.ui \
    registration.ui \
    user.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
