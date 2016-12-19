#-------------------------------------------------
#
# Project created by QtCreator 2016-11-16T04:16:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleInterpreter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    token.cpp \
    parser.cpp \
    identifier.cpp \
    implementer.cpp \
    expression.cpp \
    treeexpressions.cpp

HEADERS  += mainwindow.h \
    token.h \
    parser.h \
    identifier.h \
    implementer.h \
    expression.h \
    treeexpressions.h

FORMS    += mainwindow.ui
