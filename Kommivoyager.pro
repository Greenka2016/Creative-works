QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    deledgeform.cpp \
    delvertform.cpp \
    main.cpp \
    graph.cpp \
    newedgeform.cpp \
    newmatrixform.cpp

HEADERS += \
    deledgeform.h \
    delvertform.h \
    graph.h \
    newedgeform.h \
    newmatrixform.h

FORMS += \
    deledgeform.ui \
    delvertform.ui \
    graph.ui \
    newedgeform.ui \
    newmatrixform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
