#  @file    Makefile
#
#  @brief   Unix Make tool configuration file.
#
#  @usage   Enter make help for informations.
#
#  @bug     This Makefile need some updates..
#  @warning
#  @todo    Make install should install library to /usr/lib and include files,
#           it would be nice to have a ./configure too.
#
#  @version 1.0
#  @date    28/11/2005 - 03/07/2008
#  @author  Alessandro Polo - Nicola Conci
#
#
#############################################################################
# VIPLib Framework 1.1
# Multimedia Signal Processing and Understanding Lab (http://mmlab.disi.unitn.it) 
# Project founder: Alessandro Polo
#
#############################################################################



CC=	g++
C=	gcc
AR=	ar
RANLIB=	ranlib 
IDIR=	./include
LIBDIR=	./lib
FLAGS=	-I$(IDIR)  -L$(LIBDIR)
CCFLAGS=$(FLAGS)
#CCFLAGS=$(FLAGS) -g -Wall -O3
CFLAGS=	$(FLAGS) -g -Wall -O3


SRCS=	./source/vipFrameYUV420.cpp	\
	./source/vipFrameYUV444.cpp	\
	./source/vipFrameRGB24.cpp	\
	./source/vipFrameRGB96.cpp	\
	./source/vipFrameHSV.cpp	\
	./source/vipFrameGrey.cpp	\
	./source/vipInput.cpp	\
	./source/vipProcess.cpp	\
	./source/vipObject.cpp	\
	./source/vipFilter.cpp	\
	./source/vipHist.cpp	\
	./source/vipUtility.cpp \
	./source/vipVision.cpp	\
	./source/math/vipStatistics.cpp	\
	./source/filters/vipDigitalFilter.cpp	\
	./source/filters/vipMultiplexer.cpp	\
	./source/filters/vipFilterNoiseChannel.cpp	\
	./source/filters/vipFilterGeometric.cpp	\
	./source/filters/vipFilterColor.cpp	\
	./source/filters/vipFilterMorphological.cpp \
	./source/inputs/vipNoiseGenerator.cpp	\
	./source/inputs/vipPlainFrameGenerator.cpp	\
	./source/outputs/vipDoctor.cpp	\
	./source/outputs/vipOuputVoid.cpp	\
	./source/vision/vipMotionLame.cpp	\
	./source/vision/vipMotionIlluminationInvariant.cpp	\
	./source/codecs/vipCodec_BMP.cpp	\
	./source/codecs/external_BMP/MicrosoftBMP_RT.cpp	\
	./source/codecs/external_BMP/MicrosoftMonoBMP_RT.cpp	\
	./source/codecs/external_BMP/MicrosoftRCBMP_RT.cpp \
	./source/codecs/vipCodec_RAW.cpp 
	

OBJS=  $(SRCS:.cpp=.o)

LIBS=    -lstdc++

.SUFFIXES: .cpp .o

.cpp.o:
	$(CC) $(CCFLAGS) -c $< $(OUTPUT_OPTION)

.c.o:
	$(C) $(CFLAGS) -c $< $(OUTPUT_OPTION)

$(OBJS):   $(INCLUDE) 

VIPLIB= ./lib/VIPLib.a

VIPL= VIPLib
V4L= v4l
GUI = gui


#################################################################


# 'make all' is equal to 'make VIPLib'

all:	$(OBJS) Makefile
	@ echo 
	@ echo VIPLib Make: VIPLib!
	@ echo 
	@ echo Making VIPLib light 	
	@ $(RANLIB) $(VIPLIB)
	@ echo Making done.
	@ echo 
	@ echo VIPLib Make: Finished.
	@ echo 


big:	$(OBJS) Makefile
	@ echo 
	@ echo VIPLib Make: VIPLib!
	@ echo 
	@ echo Making VIPLib with ImageMagick, Video4Linux, XVID, MPEG, QT, support... 

	@ $(CC) -c ./source/inputs/vipVideo4Linux.cpp -o ./source/inputs/vipVideo4Linux.o
	@ $(AR) r $(VIPLIB) $(OBJS) ./source/inputs/vipVideo4Linux.o

	@ $(CC) -I/usr/include/qt4  -c ./source/outputs/vipWindowQT.cpp -o ./source/outputs/vipWindowQT.o
	@ $(AR) r $(VIPLIB) $(OBJS) ./source/outputs/vipWindowQT.o

	@ $(RANLIB) $(VIPLIB)
	@ echo Making done.
	@ echo 
	@ echo VIPLib Make: Finished.
	@ echo 
	



# Removing objects (.o) and VIPLib file.
clean:
	@ echo 
	@ echo VIPLib Make: Cleaning!
	@ echo 
	@ echo -n Removing Objects..
	@ cd source; rm -r -f *.o; cd ..;
	@ echo .. done.
	@ echo -n Removing VIPLib..
	@ rm -f $(VIPLIB)
	@ echo .. done.
	@ echo 
	@ echo VIPLib Make: Finished.
	@ echo 




# 'make VIPLib' contruct library of object files.
# ar rvu lib.a x.o y.o	
# ranlib lib.a


$(VIPL): $(OBJS) Makefile
	@ echo 
	@ echo VIPLib Make: VIPLib!
	@ echo 
	@ echo Making $(VIPLIB) ... 
	@ $(AR) r $(VIPLIB) $(OBJS)


$(V4L): $(OBJS) Makefile
	@ echo 
	@ echo VIPLib Make: VIPLib!
	@ echo 
	@ echo Making VIPLib with Video4Linux support... 
	@ $(CC) -c ./source/inputs/vipVideo4Linux.cpp -o ./source/inputs/vipVideo4Linux.o
	@ $(AR) r $(VIPLIB) $(OBJS) ./source/inputs/vipVideo4Linux.o
	@ $(RANLIB) $(VIPLIB)
	@ echo Making done.
	@ echo 
	@ echo VIPLib Make: Finished.
	@ echo 

$(GUI): $(OBJS) Makefile
	@ echo 
	@ echo VIPLib Make: VIPLib!
	@ echo 
	@ echo Making VIPLib with GUI support...  (QT library)
	@ $(CC) -c ./source/outputs/vipWindowQT.cpp -o ./source/outputs/vipWindowQT.o
	@ $(AR) r $(VIPLIB) $(OBJS) ./source/outputs/vipWindowQT.o 
	@ $(RANLIB) $(VIPLIB)
	@ echo Making done.
	@ echo 
	@ echo VIPLib Make: Finished.
	@ echo
	


help:
	@ echo 
	@ echo VIPLib Test Make: HELP!
	@ echo =======================
	@ echo 
	@ echo  Available Tests:
	@ echo 
	@ echo .	$(VIPL)		[standard library]
	@ echo 
	@ echo .	$(GUI)		[GUI support: QT] *
	@ echo .	$(V4L)		[Video4Linux support] *
	@ echo 
	@ echo  Usage:
	@ echo 		 Make all	: Build with all options.
	@ echo 		 Make 'option'	: Build with selected support.
	@ echo 		 Make clean	: Remove intermediate objects.
	@ echo 
	@ echo 
	@ echo  Output is located in ./lib/VIPLib.a
	@ echo 
	@ echo  * need external libraries (check ./COMPILE and ./support/NOTES)
	@ echo 
	@ echo 

