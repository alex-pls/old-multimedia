# QMAKE Configuration file
# Copyright (c) 2009, WOSH - Wide Open Smart Home 
# by Alessandro Polo - OpenSmartHome.com
# All rights reserved.
#######################################################
# Revision $Id: test_LibVlc086c.pro 435 2009-08-21 02:15:11Z alex $
#######################################################

CONFIG += console rtti stl exceptions thread moc
QT -= gui

DEPENDPATH += .
INCLUDEPATH += . ../../../

LIBS += -lvlc

SOURCES += test_LibVlc086c.cpp

TEMPLATE = app
TARGET = test_LibVlc086c
