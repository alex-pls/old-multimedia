#  @file    ./packages/templates/MakeFile
#
#  @brief   Unix Make tool configuration file.
#
#  @usage   Enter make ....
#
#
#  @bug
#  @warning
#  @todo
#
#
#  @version 0.56
#  @date    28/07/2005 - //2005
#  @author  Alessandro Polo
#
#
#############################################################################
# VIPLib Framework
#  open source, founded by Alessandro Polo 2006
#  http://mmlab.science.unitn.it/projects/VIPLib
#
#  maintained by MultiMedia Laboratory - DIT - University of Trento
#
#############################################################################

#g++ -I../include -lstdc++ -g -Wall -O3 test_vipCoder_BMP.cpp ../lib/VIPLib.a -o test_vipCoder_BMP.out

CC	=	g++
C	=	gcc
IDIR	=	../../include
VIPLIB	=	VIPLib.a
LIBDIR	=	../../lib/
BIN	=	./
FLAGS	=	-I$(IDIR)
LIBS	=	$(LIBDIR)/$(VIPLIB)
CCFLAGS	=	$(FLAGS) -g -Wall -O3
CFLAGS	=	$(FLAGS) -g -Wall -O3



SRCS	=	

OBJS	=	 $(SRCS:.cpp=.o)


.SUFFIXES:
	.cpp .o

.cpp.o:
	$(CC) $(CCFLAGS) -c $< $(OUTPUT_OPTION)

.c.o:
	$(C) $(CFLAGS) -c $< $(OUTPUT_OPTION)

$(OBJS):   $(INCLUDE) 


T_VIPOUTPUTDWT	=	vipOutputDWT


#################################################################


all:
	@ echo VIPLib Package Making vipOutputDWT
	@ echo =====================================

	make $(T_VIPOUTPUTDWT)
	@ echo
	@ echo
	@ echo VIPLib Package Make: Finished.
	@ echo 

# Removing objects (.o) and tests executables.
clean:
	@ echo 
	@ echo VIPLib Package Make: Cleaning!
	@ echo 
	@ echo -n Removing Objects..
	@ rm -f -R *.o
	@ echo .. done.
	@ echo -n Removing VIPLib Packages files..
	@ rm -f *.out core
	@ echo .. done.
	@ echo 
	@ echo VIPLib Tests Make: Finished.
	@ echo 


$(T_VIPOUTPUTDWT): $(OBJS) Makefile
	@ echo 
	@ echo VIPLib Package Making: $(T_VIPOUTPUTDWT)
	@ $(CC) $(CCFLAGS) test_vipOutputDWT.cpp $(LIBS) -o $(BIN)test_vipOutputDWT.out
	@ echo ..done
	@ echo 


help:
	@ echo 
	@ echo VIPLib Package Make: HELP!
	@ echo =========================
	@ echo 
	@ echo 
	@ echo 
	@ echo  Usage:
	@ echo 		 Make all	: Compile and Link all tests.
	@ echo 		 Make 'option'	: Compile and Link selected test.
	@ echo 		 Make clean	: Remove intermediate objects.
	@ echo 
	@ echo 
	@ echo 
	@ echo 
	@ echo 

