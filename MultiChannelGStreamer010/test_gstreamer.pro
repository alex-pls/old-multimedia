# QMAKE Configuration file
# Copyright (c) 2009, WOSH - Wide Open Smart Home 
# by Alessandro Polo - OpenSmartHome.com
# All rights reserved.
#######################################################
# Revision $Id: test_gstreamer.pro 435 2009-08-21 02:15:11Z alex $
#######################################################

CONFIG += console rtti stl exceptions thread moc
QT -= gui

DEPENDPATH += .
INCLUDEPATH += . ../../../

OBJECTS_DIR = ../../../../tmp/PlayerGS


CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-0.10

HEADERS += PlayerGStreamer010.h
SOURCES += PlayerGStreamer010.cpp

SOURCES += test_gstreamer_mt.cpp
#SOURCES += test_gstreamer.cpp

TEMPLATE = app
TARGET = test_PlayerGS

LIBS += -L../../../../lib
LIBS += -lcore

########################################################################
