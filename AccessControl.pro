#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T10:40:14
#
#-------------------------------------------------

include(3rdparty\QtXlsxWriter\src\xlsx\qtxlsx.pri)


QT      += core gui sql serialport
QT      += printsupport
QT      += axcontainer
QT      += multimedia
QT      += sql
QT      += core network sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = AccessControl
TEMPLATE = app
INCLUDEPATH += incluide
INCLUDEPATH += people

RESOURCES = comboscan.qrc

SOURCES += main.cpp\
        dashboard.cpp \
    connection.cpp \
    login.cpp \
    logger.cpp \
    exportrecords.cpp \
    people.cpp \
    readwithoutci.cpp \
    users.cpp \
    companies.cpp \
    positions.cpp \
    userprofile.cpp \
    individualreport.cpp \
    rejectedreport.cpp \
    configuration.cpp \
    dailyreport.cpp \
    formcs.cpp

HEADERS  += dashboard.h \
    connection.h \
    login.h \
    logger.h \
    exportrecords.h \
    people.h \
    readwithoutci.h \
    users.h \
    companies.h \
    positions.h \
    userprofile.h \
    individualreport.h \
    rejectedreport.h \
    configuration.h \
    dailyreport.h \
    formcs.h

FORMS    += dashboard.ui \
    login.ui \
    logger.ui \
    exportrecords.ui \
    people.ui \
    readwithoutci.ui \
    users.ui \
    companies.ui \
    positions.ui \
    userprofile.ui \
    individualreport.ui \
    rejectedreport.ui \
    configuration.ui \
    dailyreport.ui \
    formcs.ui

