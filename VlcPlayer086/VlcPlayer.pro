# QMAKE Configuration file
# Copyright (c) 2009, WOSH - Wide Open Smart Home 
# by Alessandro Polo - OpenSmartHome.com
# All rights reserved.
#######################################################
# Revision $Id: VlcPlayer.pro 435 2009-08-21 02:15:11Z alex $
#######################################################

CONFIG += console rtti stl exceptions thread moc
QT -= gui

DEPENDPATH += .
INCLUDEPATH += . ../../../

OBJECTS_DIR = ../../../../tmp/VlcPlayer

LIBS += -lvlc

HEADERS += VlcPlayer086c.h
SOURCES += VlcPlayer086c.cpp
#HEADERS += VlcPlayer099.h
#SOURCES += VlcPlayer099.cpp

HEADERS += VlcPlayer.h
HEADERS += IVlcPlayerListener.h

HEADERS += VlcPlayerBundle.h
SOURCES += VlcPlayerBundle.cpp


########################################################################
# custom building setting (will override)
!include( ../devices.pri ) {
	message( "*****  No custom build options specified. *****" )
	message( "*****  Building Bundles - Devices - VlcPlayer TEST *****" )
	#CONFIG += make_app_test
} 

#CONFIG += make_lib_static
#CONFIG += make_lib_shared
#CONFIG += make_plugin
#CONFIG += make_app_test
########################################################################


########################################################################
############################################################# LIB STATIC
make_lib_static  {
	message("WOSH Framework - Bundles - Devices - VlcPlayer - LIB STATIC")

	TEMPLATE = lib
	CONFIG += staticlib
	TARGET = bundleVlcPlayer
	DESTDIR = ../../../../lib

}
########################################################################
############################################################# LIB SHARED
make_lib_shared {
	message("WOSH Framework - Bundles - Devices - VlcPlayer - LIB SHARED")

	TEMPLATE = lib
	TARGET = bundleVlcPlayer
	DESTDIR = ../../../../lib

}
########################################################################
################################################################# PLUGIN
make_plugin {
	message("WOSH Framework - Bundles - Devices - VlcPlayer - PLUGIN")

	TEMPLATE = lib
	TARGET = plugin_VlcPlayerBundle
	DESTDIR = ../../../../bin

	SOURCES += plugin_VlcPlayerBundle.cpp

}
########################################################################
########################################################################
############################################################### APP TEST
make_app_test {
	message("WOSH Framework - Bundles - Devices - VlcPlayer - APP TEST")

	TEMPLATE = app
	TARGET = test_VlcPlayer
#	DESTDIR = ../../../../bin

	LIBS += -L../../../../lib
	LIBS += -lcore

	HEADERS -= VlcPlayerBundle.h
	SOURCES -= VlcPlayerBundle.cpp

	SOURCES += test_VlcPlayer.cpp

}
########################################################################
